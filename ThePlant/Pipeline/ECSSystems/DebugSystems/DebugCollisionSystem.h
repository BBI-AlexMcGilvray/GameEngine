#pragma once

#include <algorithm>

#include "Core/Logging/Logger.h"
#include "Core/Math/Headers/MathDefs.h"

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/2D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application
{
struct DebugCollisionSystem : public System<DebugCollisionSystem>
{
    DebugCollisionSystem(Collision::CollisionManager& collisionManager, Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : _collisionManager(collisionManager)
    , _renderManager(renderManager)
    , _meshGetter(*this)
    {
        _debugMaterial = Rendering::CreateDefaultMaterial(shaderManager);
        
        _lineMesh = Rendering::CreateLine(1.0f);
        _pointMesh = Rendering::CreateSphere(0.1f);

        _circleMesh = Rendering::CreateCircle(1.0f);
        _rectangleMesh = Rendering::CreateRectangle(1.0f);

        _boxMesh = Rendering::CreateBox(1.0f);
        _sphereMesh = Rendering::CreateSphere(1.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent, ColliderComponent>();
        const auto allCollisions = _collisionManager.GetAllCollisions();

        for (auto& archetype : affectedArchetypes)
        {
            if (archetype->HasComponent<CameraComponent>())
            {
                // hack fix to not draw the shape for the camera since it covers everything
                continue;
            }
            _ApplyToArchetype(allCollisions, archetype->GetEntities(), archetype->GetComponents<WorldTransformComponent>(), archetype->GetComponents<ColliderComponent>());
        }
    }

private:
    // we need to handle lines, and planes as well
    struct MeshGetter
    {
        MeshGetter(const DebugCollisionSystem& debugSystem)
        : _debugSystem(debugSystem)
        {}

        Rendering::Mesh operator()(const Core::Geometric::Box& box) const { return _debugSystem._boxMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Circle& circle) const { return _debugSystem._circleMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Line2D& line) const { return _debugSystem._lineMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Line3D& line) const { return _debugSystem._lineMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Plane& plane) const { return (plane.infinite ? _debugSystem._rectangleMesh : std::visit(*this, plane.shape)); }
        Rendering::Mesh operator()(const Core::Geometric::Spot2D& point) const { return _debugSystem._pointMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Spot3D& point) const { return _debugSystem._pointMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Rectangle& rectangle) const { return _debugSystem._rectangleMesh; }
        Rendering::Mesh operator()(const Core::Geometric::Sphere& sphere) const { return _debugSystem._sphereMesh; }

    private:
        const DebugCollisionSystem& _debugSystem;
    };

    struct DrawTypeGetter
    {
        Rendering::DrawType operator()(const Core::Geometric::Line2D& line) const { return Rendering::DrawType::LINE; }
        Rendering::DrawType operator()(const Core::Geometric::Line3D& line) const { return Rendering::DrawType::LINE; }
        template <typename T>
        Rendering::DrawType operator()(const T& otherType) const { return Rendering::DrawType::TRIANGLE; }
    };

    struct ScaleGetter
    {
        Core::Math::Float3 operator()(const Core::Geometric::Box& box) const { return box.dimensions; }
        Core::Math::Float3 operator()(const Core::Geometric::Circle& circle) const { return Core::Math::Float3(circle.radius); }
        Core::Math::Float3 operator()(const Core::Geometric::Line2D& line) const { return Core::Math::Float3(line.infinite ? std::numeric_limits<float>::max() : line.length); }
        Core::Math::Float3 operator()(const Core::Geometric::Line3D& line) const { return Core::Math::Float3(line.infinite ? std::numeric_limits<float>::max() : line.length); }
        Core::Math::Float3 operator()(const Core::Geometric::Plane& plane) const { return (plane.infinite ? Core::Math::Float3(std::numeric_limits<float>::max()) : std::visit(*this, plane.shape)); }
        Core::Math::Float3 operator()(const Core::Geometric::Spot2D& point) const { return Core::Math::Float3(1.0f); }
        Core::Math::Float3 operator()(const Core::Geometric::Spot3D& point) const { return Core::Math::Float3(1.0f); }
        Core::Math::Float3 operator()(const Core::Geometric::Rectangle& rectangle) const { return Core::Math::Float3(rectangle.dimensions, 1.0f); }
        Core::Math::Float3 operator()(const Core::Geometric::Sphere& sphere) const { return Core::Math::Float3(sphere.radius); }
    };

    Collision::CollisionManager& _collisionManager;
    Rendering::RenderManager& _renderManager;

    Rendering::Material _debugMaterial;
    MeshGetter _meshGetter;
    DrawTypeGetter _typeGetter;
    ScaleGetter _scaleGetter;

    // Both
    Rendering::Mesh _lineMesh;
    Rendering::Mesh _pointMesh;

    // 2D
    Rendering::Mesh _circleMesh;
    Rendering::Mesh _rectangleMesh;
    // what do we do for line2D? what about if it is infinite length?

    // 3D
    Rendering::Mesh _boxMesh;
    Rendering::Mesh _sphereMesh;
    // what do we do for planes? just use the relevant 2D mesh?
    // what do we do for line3D? what about if it is infinite length?

    void _ApplyToArchetype(const std::vector<Collision::Collision>& allCollisions, const std::vector<EntityId>& entities, std::vector<WorldTransformComponent>& worldTransforms, std::vector<ColliderComponent>& colliderComponents) const
    {
        VERIFY(worldTransforms.size() == colliderComponents.size());
        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            Core::Geometric::Transform scaleAdjustedTransform = worldTransforms[index].transform;
            // below adjusts the transform scale to also take into account the shape relative scale (relative to the default value for each which is 1.0f - except radius is 0.5f)
            scaleAdjustedTransform.AdjustScale(std::visit(_scaleGetter, colliderComponents[index].shape));

            const bool inCollision = std::find_if(allCollisions.begin(), allCollisions.end(), [&allCollisions, &entities, index](const auto& collision)
            {
                return (collision.entity1.GetEntity() == entities[index] || collision.entity2.GetEntity() == entities[index]);
            }) != allCollisions.end();

            Core::Math::Color colliderColor = colliderComponents[index].trigger ? Core::Math::BLUE : Core::Math::YELLOW;
            if (inCollision)
            {
                colliderColor = colliderComponents[index].trigger ? Core::Math::GREEN : Core::Math::RED;
            }
            Rendering::Mesh colliderMesh = std::visit(_meshGetter, colliderComponents[index].shape);
            Rendering::DrawType drawType = std::visit(_typeGetter, colliderComponents[index].shape);

            Rendering::Context context = {
                _debugMaterial,
                scaleAdjustedTransform.GetTransformationMatrix(),
                colliderColor,
                colliderMesh,
                Rendering::DrawMode::LINE,
                drawType
            };
            _renderManager.QueueRender(context);
        }
    }
};
} // namespace Application