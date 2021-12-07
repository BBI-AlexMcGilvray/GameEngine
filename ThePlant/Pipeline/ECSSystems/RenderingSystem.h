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
struct MeshRenderingSystem : public System<MeshRenderingSystem, MaterialComponent, MeshComponent, WorldTransformComponent>
{
    MeshRenderingSystem(Rendering::RenderManager& renderManager)
    : _renderManager(renderManager)
    {}

    static void ApplyToArchetype(std::vector<MaterialComponent>& materialComponents, std::vector<MeshComponent>& meshComponents, std::vector<WorldTransformComponent>& transformComponents)
    {
        VERIFY(materialComponents.size() == meshComponents.size() == transformComponents.size());

        for (size_t index = 0; index < materialComponents.size(); ++index)
        {
            Rendering::Context context = {
                materialComponents[index].material,
                transformComponents[index].transform.GetTransformationMatrix(),
                Core::Math::WHITE, // this should be gotten from the ColorComponent if the archetype has it
                meshComponents[index].mesh
            };
            _renderManager.QueueRender(context); // if we do more custom logic for handling of this, the rendererManager should be passed in as a parameter
        }
    }

private:
    Rendering::RenderManager& _renderManager;
};

// should take values from world transform and writes to the array of transforms for the bones
struct SkeletonUpdateSystem : public System<SkeletonUpdateSystem, SkeletonComponent, WorldTransformComponent>
{

};

struct SkinnedMeshRenderingSystem : public System<SkinnedMeshRenderingSystem, MaterialComponent, SkinnedMeshComponent, WorldTransformComponent>
{
    static void ApplyToArchetype(std::vector<MaterialComponent>& materialComponents, std::vector<SkinnedMeshComponent>& skinnedMeshComponents, std::vector<WorldTransformComponent>& transformComponents)
    {
        VERIFY(materialComponents.size() == skinnedMeshComponents.size() == transformComponents.size());

        for (size_t index = 0; index < materialComponents.size(); ++index)
        {
            
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