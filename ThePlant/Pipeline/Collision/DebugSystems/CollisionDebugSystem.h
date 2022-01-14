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
struct CollisionDebugSystem
{
    CollisionDebugSystem(Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)

private:
    // create a mesh for each shape (default mesh, scaled to 1.0f for everything)
    // when using these meshes, modify the scale of the transform passed in to be multiplied by the scale of the collider (relative to the default 1.0) being used
};

// don't forget the debug system
} // namespace Collision
} // namespace Application