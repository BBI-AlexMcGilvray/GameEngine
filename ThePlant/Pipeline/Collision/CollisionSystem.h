#pragma once

#include "Pipeline/Collision/ColliderComponent.h"
#include "Pipeline/Collision/Collision.h"
#include "Pipeline/Collision/OctTree.h"

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application
{
namespace Collision
{
struct CollisionSystem
{
    CollisionSystem(ECS& ecs)

private:
    ECS& _ecs;
};
} // namespace Collision
} // namespace Application