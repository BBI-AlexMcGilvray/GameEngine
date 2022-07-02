#pragma once

#include "Core/Debugging/Headers/Declarations.h"

namespace Application
{
// may be beneficial to use a struct to map enum->type to potentially limit mistakes. could do a constexpr for loop for the enum values as well
// that would help ensure all enum values are covered

enum class ECSSystem
{
    AnimationSystem = 1 << 0,
    CameraSystem = 1 << 1,
    CollisionSystem = 1 << 2,
    RenderingSystem = 1 << 3,
    TransformSystem = 1 << 4,
    PhysicsSystem = 1 << 5,
    VelocitySystem = 1 << 6
#if DEBUG // Debug system only after this
    , // to continue list above
    DebugBoneSystem = 1 << 30, // count from the other direction so debug systems are always the last
    DebugCollisionSystem = 1 << 29,
    DebugOctTreeSystem = 1 << 28,
    DebugTransformSystem = 1 << 27
#endif
};

enum class CollisionHandler
{
    RigidBodyCollision = 1 << 0
#if DEBUG // Debug system only after this
    , // to continue list above
    DebugCollisionDisplay = 1 << 30
#endif
};
} // namespace Application