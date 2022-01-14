#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
struct DebugTransformSystem : public System<DebugTransformSystem>
{
    DebugTransformSystem(Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : _renderManager(renderManager)
    {
        _transformMaterial = CreateDefaultMaterial(shaderManager);
        _transformMesh = Rendering::CreateSphere(25.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            if (archetype->HasComponent<CameraComponent>())
            {
                // hack fix to not draw the shape for the camera since it covers everything
                continue;
            }
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
                Core::Math::BLUE,
                _transformMesh
            };
            _renderManager.QueueRender(context);
        }
    }
};
}// namespace Application