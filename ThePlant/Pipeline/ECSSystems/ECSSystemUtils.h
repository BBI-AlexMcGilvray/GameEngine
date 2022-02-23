#pragma once

#include "Core/Debugging/Headers/Declarations.h"

namespace Application
{
enum class ECSSystem
{
    AnimationSystem = 1 << 0,
    CameraSystem = 1 << 1,
    CollisionSystem = 1 << 2,
    RenderingSystem = 1 << 3,
    TransformSystem = 1 << 4
#if DEBUG // Debug system only after this
    , // to continue list above
    DebugBoneSystem = 1 << 30, // count from the other direction so debug systems are always the last
    DebugCollisionSystem = 1 << 29,
    DebugOctTreeSystem = 1 << 28,
    DebugTransformSystem = 1 << 27
#endif
};
} // namespace Application