#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
struct DebugBoneSystem : public System<DebugBoneSystem>
{
    DebugBoneSystem(Rendering::RenderManager& renderManager, Rendering::MaterialManager& materialManager)
    : System<DebugBoneSystem>("DebugBoneSystem")
    , _renderManager(renderManager)
    {
        _transformMaterial = materialManager.GetDefaultMaterial();
        _transformMesh = Rendering::CreatePyramid(100.0f, 25.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());
        
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent, BoneComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype->GetComponents<WorldTransformComponent>());
        }
    }

private:
    Rendering::Material _transformMaterial;
    Rendering::Mesh _transformMesh;
    Rendering::RenderManager& _renderManager;

    void _ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms) const
    {
        for (auto& worldTransform : worldTransforms)
        {
            Core::Geometric::Transform lockedScale = worldTransform.transform;
            lockedScale.SetScale(1.0f);

            Rendering::Context context = {
                _transformMaterial,
                lockedScale.GetTransformationMatrix(),
                Core::Math::GREEN,
                _transformMesh
            };
            _renderManager.QueueRender(context);
        }
    }
};
}// namespace Application