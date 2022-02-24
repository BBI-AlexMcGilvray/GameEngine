#pragma once

#include <vector>

#include "Pipeline/Collision/Collision.h"
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
    DebugCollisionDisplay(Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : CollisionHandler<DebugCollisionDisplay>("DebugCollisionDisplay", CollectTypes<WorldTransformComponent>(), CollectTypes<WorldTransformComponent>(), false)
    , _renderManager(renderManager)
    {
        _collisionPointMaterial = CreateDefaultMaterial(shaderManager);
        _collisionPointMesh = Rendering::CreateSphere(0.5f);
    }

private:
    Rendering::Material _collisionPointMaterial;
    Rendering::Mesh _collisionPointMesh;
    Rendering::RenderManager& _renderManager;

    void _Apply(EntitySnapshot& from, EntitySnapshot& to) const override
    {
        const Core::Geometric::Transform& fromTransform = from.GetComponent<WorldTransformComponent>().transform;
        const Core::Geometric::Transform& toTransform = to.GetComponent<WorldTransformComponent>().transform;
        
        Core::Geometric::Transform middlePointTransform((fromTransform.GetPosition() + toTransform.GetPosition()) * 0.5f);
        middlePointTransform.SetScale(0.25f); // debug system, just needs to be visible

        Rendering::Context context = {
            _collisionPointMaterial,
            middlePointTransform.GetTransformationMatrix(),
            Core::Math::BLACK,
            _collisionPointMesh
        };
        _renderManager.QueueRender(context);
    }
};
} // namespace Collision
}// namespace Application