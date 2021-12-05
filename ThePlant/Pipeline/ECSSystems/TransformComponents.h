#pragma once

#include "Materials/Core/Geometric/Headers/Transform.h"
#include "Materials/Core/Math/Headers/Quaternion.h"
#include "Materials/Core/Math/Headers/Vector3.h"

namespace Application {
struct PositionComponent
{
    Core::Math::Float3 position;
};

struct ScaleComponent
{
    Core::Math::Float3 scale;
};

struct RotationComponent
{
    Core::Math::FQuaternion rotation;
};

struct LocalTransformComponent
{
    Core::Geometric::Transform transform;
};

struct WorldTransformComponent
{
    Core::Geometric::Transform transform;
};
}// namespace Application