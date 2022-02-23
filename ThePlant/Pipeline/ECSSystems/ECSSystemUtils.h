#pragma once

#include "Core/Debugging/Headers/Declarations.h"

namespace Application
{
enum class ECSSystem
{
    AnimationSystem,
    CameraSystem,
    CollisionSystem,
    RenderingSystem,
    TransformSystem
#if DEBUG
// Debug system only after this
    , // to continue list above
    DebugBoneSystem,
    DebugCollisionSystem,
    DebugOctTreeSystem,
    DebugTransformSystem
#endif
};
} // namespace Application