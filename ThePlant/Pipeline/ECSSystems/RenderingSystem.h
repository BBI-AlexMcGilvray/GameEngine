#pragma once

#include <unordered_map>
#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
// do we want two systems (one for this, one that takes into account a color component)?
// or should we instead have higher-level logic in here that checks each archetype (that matches the rest) for also the color component?
// probably the second?
struct MeshRenderingSystem : public System<MeshRenderingSystem>
{
    MeshRenderingSystem(Rendering::RenderManager& renderManager)
    : System<MeshRenderingSystem>()
    , _renderManager(renderManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<MaterialComponent, MeshComponent, WorldTransformComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype);
        }
    }

private:
    Rendering::RenderManager& _renderManager;

    void _ApplyToArchetype(Core::Ptr<Archetype> archetype) const
    {
        std::vector<MaterialComponent>& materials = archetype->GetComponents<MaterialComponent>();
        std::vector<MeshComponent>& meshes = archetype->GetComponents<MeshComponent>();
        std::vector<WorldTransformComponent>& transforms = archetype->GetComponents<WorldTransformComponent>();
        Core::Ptr<std::vector<ColorComponent>> colors = archetype->HasComponent<ColorComponent>() ? &(archetype->GetComponents<ColorComponent>()) : nullptr;

        DEBUG_ASSERT((materials.size() == meshes.size()) && (materials.size() == transforms.size()));
        DEBUG_ASSERT(colors == nullptr || colors->size() == materials.size());

        for (size_t index = 0; index < materials.size(); ++index)
        {
            Rendering::Context context = {
                materials[index].material,
                transforms[index].transform.GetTransformationMatrix(),
                colors == nullptr ? Core::Math::WHITE : (*colors)[index].color,
                meshes[index].mesh
            };
            _renderManager.QueueRender(context);
        }
    }
};

// should take values from world transform and writes to the array of transforms for the bones
struct SkeletonUpdateSystem : public System<SkeletonUpdateSystem>
{
    enum class TAG { CREATE };

    using BoneData = std::unordered_map<EntityId, std::pair<BoneComponent, WorldTransformComponent>>;

    SkeletonUpdateSystem(const TAG& tag)
    : System<SkeletonUpdateSystem>()
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::vector<Core::Ptr<Archetype>> skeletonArchetypes = archetypeManager.GetArchetypesContaining<SkeletonComponent>();
        // bones require the relative change in THEIR position to affect the mesh, NOT the world position/offset (otherwise animation would break moving any real distance)
        std::vector<Core::Ptr<Archetype>> boneArchetypes = archetypeManager.GetArchetypesContaining<BoneComponent, LocalTransformComponent>();

        BoneData boneToDataMapping = GetEntityBoneData(boneArchetypes);

        ApplyBoneDataToSkeleton(skeletonArchetypes, boneToDataMapping);
    }

private:
    static BoneData GetEntityBoneData(std::vector<Core::Ptr<Archetype>>& boneArchetypes)
    {
        BoneData boneToDataMapping;

        for (auto& boneArchetype : boneArchetypes)
        {
            const std::vector<EntityId>& entities = boneArchetype->GetEntities();
            std::vector<BoneComponent>& bones = boneArchetype->GetComponents<BoneComponent>();
            std::vector<WorldTransformComponent>& transforms = boneArchetype->GetComponents<WorldTransformComponent>();

            DEBUG_ASSERT((entities.size() == bones.size()) && (entities.size() == transforms.size()));
            for (size_t index = 0; index < entities.size(); ++index)
            {
                boneToDataMapping[entities[index]] = std::make_pair(bones[index], transforms[index]);
            }
        }

        return boneToDataMapping;
    }

    static void ApplyBoneDataToSkeleton(std::vector<Core::Ptr<Archetype>>& skeletonArchetypes, BoneData& boneToDataMapping)
    {
        for (auto& skeletonArchetype : skeletonArchetypes)
        {
            std::vector<SkeletonComponent>& skeletons = skeletonArchetype->GetComponents<SkeletonComponent>();

            for (auto& skeleton : skeletons)
            {
                auto& rootBone = boneToDataMapping.at(skeleton.rootBone).second;
                for (size_t boneIndex = 0; boneIndex < skeleton.nameAndEntities.size() && skeleton.nameAndEntities[boneIndex].second.IsValid(); ++boneIndex)
                {
                    auto& entityData = boneToDataMapping.at(skeleton.nameAndEntities[boneIndex].second);
                    const auto& relativeToRootBoneTransform = rootBone.transform.GetInverseTransformationMatrix() * entityData.second.transform.GetTransformationMatrix();
                    const auto& relativeTransform = relativeToRootBoneTransform * entityData.first.bindMatrix;
                    skeleton.boneArray[boneIndex] = relativeTransform;
                }
            }
        }
    }
};

struct SkinnedMeshRenderingSystem : public System<SkinnedMeshRenderingSystem>
{
    SkinnedMeshRenderingSystem(Rendering::RenderManager& renderManager)
    : System<SkinnedMeshRenderingSystem>()
    , _renderManager(renderManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());
        
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<MaterialComponent, SkinnedMeshComponent, SkeletonComponent, WorldTransformComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype);
        }
    }

private:
    Rendering::RenderManager& _renderManager;

    void _ApplyToArchetype(Core::Ptr<Archetype> archetype) const
    {
        std::vector<MaterialComponent>& materials = archetype->GetComponents<MaterialComponent>();
        std::vector<SkinnedMeshComponent>& meshes = archetype->GetComponents<SkinnedMeshComponent>();
        std::vector<SkeletonComponent>& skeletons = archetype->GetComponents<SkeletonComponent>();
        std::vector<WorldTransformComponent>& transforms = archetype->GetComponents<WorldTransformComponent>();
        Core::Ptr<std::vector<ColorComponent>> colors = archetype->HasComponent<ColorComponent>() ? &(archetype->GetComponents<ColorComponent>()) : nullptr;

        DEBUG_ASSERT((materials.size() == meshes.size()) && (meshes.size() == transforms.size()));
        DEBUG_ASSERT(colors == nullptr || colors->size() == materials.size());

        for (size_t index = 0; index < materials.size(); ++index)
        {
            Rendering::Context context = {
                materials[index].material,
                transforms[index].transform.GetTransformationMatrix(),
                colors == nullptr ? Core::Math::WHITE : (*colors)[index].color,
                meshes[index].skinnedMesh.mesh
            };
            Rendering::SkinnedContext skinnedContext = {
                context,
                skeletons[index].boneArray
            };
            _renderManager.QueueRender(skinnedContext);
        }
    }
};

struct CameraRenderingSystem : public System<CameraRenderingSystem>
{
    CameraRenderingSystem(Rendering::RenderManager& renderManager)
    : System<CameraRenderingSystem>()
    , _renderManager(renderManager)
    , _cameraManager(renderManager.GetCameraManager())
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());
        
        for (const auto& camera : _cameraManager.GetCameras())
        {
            _renderManager.QueueCamera(camera);
        }
    }

private:
    Rendering::RenderManager& _renderManager;
    Rendering::CameraManager& _cameraManager;
};

// must be made dependent on the TransformSystem
struct RenderingSystem : public CompoundSystem<RenderingSystem,
MeshRenderingSystem,
SkeletonUpdateSystem,
SkinnedMeshRenderingSystem,
CameraRenderingSystem>
{
    RenderingSystem(Rendering::RenderManager& rendererManager)
    : CompoundSystem<RenderingSystem,
        MeshRenderingSystem,
        SkeletonUpdateSystem,
        SkinnedMeshRenderingSystem,
        CameraRenderingSystem>(rendererManager, SkeletonUpdateSystem::TAG::CREATE, rendererManager, rendererManager)
    {}
    // maybe want custom logic to handle dependency for parallel execution?
};
} // namespace Application