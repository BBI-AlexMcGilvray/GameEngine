#pragma once

#include <vector>

#include "Pipeline/Collision/Collisions.h"
#include "Pipeline/Collision/CollisionHandler.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
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
struct DebugCollisionDisplay : public CollisionHandler<DebugCollisionDisplay>
{
    DebugCollisionDisplay(Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)                                         // if we do complete here, we'll need calculate our own point, otherwise the dot shows at the origin regardless
    : CollisionHandler<DebugCollisionDisplay>("DebugCollisionDisplay", BitmaskEnum<CollisionState>(CollisionState::Initial, CollisionState::Persisting/*, CollisionState::Complete*/), CollectTypes<WorldTransformComponent>(), CollectTypes<WorldTransformComponent>(), false)
    , _renderManager(renderManager)
    {
        _collisionPointMaterial = CreateDefaultMaterial(shaderManager);
        _collisionPointMesh = Rendering::CreateSphere(0.5f);
    }

private:
    Rendering::Material _collisionPointMaterial;
    Rendering::Mesh _collisionPointMesh;
    Rendering::RenderManager& _renderManager;

    void _Apply(const CollisionState collisionState, const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        const Core::Geometric::Transform& fromTransform = from.GetComponent<WorldTransformComponent>().transform;
        const Core::Geometric::Transform& toTransform = to.GetComponent<WorldTransformComponent>().transform;
        
        Core::Geometric::Transform middlePointTransform(collisionPoint);
        middlePointTransform.SetScale(1.0f); // debug system, just needs to be visible

        Rendering::Context context = {
            _collisionPointMaterial,
            middlePointTransform.GetTransformationMatrix(),
            collisionState == CollisionState::Complete ? Core::Math::RED : Core::Math::YELLOW, // let's change the color based on the state of the collision (green/yellow/red?) -> do we need the collision sates in handlers?
            _collisionPointMesh
        };
        _renderManager.QueueRender(context);
    }
};
} // namespace Collision
}// namespace Application