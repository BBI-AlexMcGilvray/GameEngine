#pragma once

#include "Core/Debugging/Profiling/Utils.h"

#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"

namespace Application
{
namespace Collision
{
struct Collision
{
    EntitySnapshot entity1;
    EntitySnapshot entity2;
    const Core::Geometric::Point3D collisionPoint;
};

enum class CollisionState : int
{
    Initial = 1 << 0,
    Persisting = 1 << 1,
    Complete = 1 << 2
};

struct StatefulCollision : Collision
{
    CollisionState state;
};
} // namespace Collision
} // namespace Application