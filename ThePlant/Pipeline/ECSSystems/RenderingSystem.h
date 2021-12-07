#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
// do we want two systems (one for this, one that takes into account a color component)?
// or should we instead have higher-level logic in here that checks each archetype (that matches the rest) for also the color component?
// probably the second?
struct MeshRenderingSystem : public ISystem
{
    MeshRenderingSystem(Rendering::RenderManager& renderManager)
    : _renderManager(renderManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
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

        VERIFY(materials.size() == meshes.size() == transforms.size());
        VERIFY(colors == nullptr || colors->size() == materials.size());

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
struct SkeletonUpdateSystem : public System<SkeletonUpdateSystem, SkeletonComponent, WorldTransformComponent>
{
    static void ApplyToArchetype(std::vector<SkeletonComponent>& skeletonComponents, std::vector<WorldTransformComponent>& worldTransformComponents)
    {
        // need different handling, like getting all world transforms and iterating over them to find the skeleton bones, or having a special 'BoneComponent'
        // to narrow down the list of WorldTransformComponents to only those that would be relevant
    }
};

struct SkinnedMeshRenderingSystem : public ISystem
{
    SkinnedMeshRenderingSystem(Rendering::RenderManager& renderManager)
    : _renderManager(renderManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
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

        VERIFY(materials.size() == meshes.size() == transforms.size());
        VERIFY(colors == nullptr || colors->size() == materials.size());

        for (size_t index = 0; index < materials.size(); ++index)
        {
            Rendering::Context context = {
                materials[index].material,
                transforms[index].transform.GetTransformationMatrix(),
                colors == nullptr ? Core::Math::WHITE : (*colors)[index].color,
                meshes[index].mesh
            };
            Rendering::SkinnedContext skinnedContext = {
                context,
                skeletons[index].boneArray
            };
            _renderManager.QueueRender(context);
        }
    }
};

// must be made dependent on the TransformSystem
struct RenderingSystem : public CompoundSystem<RenderingSystem,
MeshRenderingSystem,
SkeletonUpdateSystem,
SkinnedMeshRenderingSystem>
{
    // maybe want custom logic to handle dependency for parallel execution?
};
} // namespace Application