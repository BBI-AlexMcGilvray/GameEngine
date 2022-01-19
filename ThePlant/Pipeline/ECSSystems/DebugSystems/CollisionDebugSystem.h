#pragma once

#include "Pipeline/Collision/ColliderComponent.h"

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application
{
namespace Collision
{
struct CollisionDebugSystem : public System<CollisionDebugSystem>
{
    CollisionDebugSystem(Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : _renderManager(renderManager)
    , _meshGetter(*this)
    {
        _debugMaterial = Rendering::CreateDefaultMaterial(shaderManager);
        
        _circleMesh = Rendering::CreateCircle(1.0f);
        _rectangleMesh = Rendering::CreateRectangle(1.0f);

        _boxMesh = Rendering::CreateBox(1.0f);
        _sphereMesh = Rendering::CreateSphere(1.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent, ColliderComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            if (archetype->HasComponent<CameraComponent>())
            {
                // hack fix to not draw the shape for the camera since it covers everything
                continue;
            }
            _ApplyToArchetype(archetype->GetComponents<WorldTransformComponent>, archetype->GetComponents<ColliderComponent>());
        }
    }

private:
    struct MeshGetter
    {
        MeshGetter(const CollisionDebugSystem& debugSystem)
        : _debugSystem(debugSystem)
        {}

        Rendering::Mesh operator()(const Geoemtric::Box& box) { return _debugSystem._boxMesh; }
        Rendering::Mesh operator()(const Geoemtric::Circle& circle) { return _debugSystem._circleMesh; }
        Rendering::Mesh operator()(const Geoemtric::Rectange& rectangle) { return _debugSystem._rectangleMesh; }
        Rendering::Mesh operator()(const Geoemtric::Sphere& sphere) { return _debugSystem._sphereMesh; }

    private:
        const CollisionDebugSystem& _debugSystem;
    };

    Rendering::RenderManager& _renderManager;

    // when using these meshes, modify the scale of the transform passed in to be multiplied by the scale of the collider (relative to the default 1.0) being used
    Rendering::Material _debugMaterial;
    MeshGetter _meshGetter;

    // 2D
    Rendering::Mesh _circleMesh;
    Rendering::Mesh _rectangleMesh;
    // what do we do for line2D? what about if it is infinite length?

    // 3D
    Rendering::Mesh _boxMesh;
    Rendering::Mesh _sphereMesh;
    // what do we do for planes? just use the relevant 2D mesh?
    // what do we do for line3D? what about if it is infinite length?

    void _ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms, std::vector<ColliderComponent>& colliderComponents) const
    {
        VERIFY(worldTransforms.size() == colliderComponents.size());
        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            Core::Geometric::Transform scaleAdjustedTransform = worldTransforms[index].transform;
            lockedScale.AdjustScale(colliderComponents[index].shape)

            // ideally we have this change based on if there was a collision for it
            Core::Math::Color colliderColor = colliderComponents[index].trigger ? Core::Math::BLUE : Core::Math::RED;
            Rendering::Mesh colliderMesh = std::visit(_meshGetter, colliderComponents[index].shape);

            // we probably want a way to set this to only draw the borders (lines instead)
            Rendering::Context context = {
                _debugMaterial,
                scaleAdjustedTransform.GetTransformationMatrix(),
                colliderColor,
                colliderMesh,
                Rendering::RenderMode::LINE
            };
            _renderManager.QueueRender(context);
        }
    }
};
} // namespace Collision
} // namespace Application