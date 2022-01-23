#pragma once

#include "Materials/Core/Geometric/Transform.h"
#include "Materials/Core/Math/Headers/Quaternion.h"
#include "Materials/Core/Math/Headers/Vector3.h"

namespace Application {
struct PositionComponent
{
    Core::Math::Float3 position;

    PositionComponent() = default;
    PositionComponent(const PositionComponent&) = default;
    PositionComponent(PositionComponent&&) = default;
    PositionComponent& operator=(const PositionComponent&) = default;
    PositionComponent& operator=(PositionComponent&&) = default;

    PositionComponent(const Core::Math::Float3& position)
    : position(position)
    {}

    bool operator==(const PositionComponent& other) const
    {
        return (position == other.position);
    }
    bool operator !=(const PositionComponent& other) const { return !(*this == other); }
};

struct ScaleComponent
{
    Core::Math::Float3 scale;

    ScaleComponent() = default;
    ScaleComponent(const ScaleComponent&) = default;
    ScaleComponent(ScaleComponent&&) = default;
    ScaleComponent& operator=(const ScaleComponent&) = default;
    ScaleComponent& operator=(ScaleComponent&&) = default;

    ScaleComponent(const Core::Math::Float3& scale)
    : scale(scale)
    {}
    
    bool operator==(const ScaleComponent& other) const
    {
        return (scale == other.scale);
    }
    bool operator !=(const ScaleComponent& other) const { return !(*this == other); }
};

struct RotationComponent
{
    Core::Math::FQuaternion rotation;

    RotationComponent() = default;
    RotationComponent(const RotationComponent&) = default;
    RotationComponent(RotationComponent&&) = default;
    RotationComponent& operator=(const RotationComponent&) = default;
    RotationComponent& operator=(RotationComponent&&) = default;

    RotationComponent(const Core::Math::FQuaternion& rotation)
    : rotation(rotation)
    {}
    
    bool operator==(const RotationComponent& other) const
    {
        return (rotation == other.rotation);
    }
    bool operator !=(const RotationComponent& other) const { return !(*this == other); }
};

struct LocalTransformComponent
{
    Core::Geometric::Transform transform;

    LocalTransformComponent() = default;
    LocalTransformComponent(const LocalTransformComponent&) = default;
    LocalTransformComponent(LocalTransformComponent&&) = default;
    LocalTransformComponent& operator=(const LocalTransformComponent&) = default;
    LocalTransformComponent& operator=(LocalTransformComponent&&) = default;

    LocalTransformComponent(const Core::Geometric::Transform& transform)
    : transform(transform)
    {}
    
    bool operator==(const LocalTransformComponent& other) const
    {
        return (transform == other.transform);
    }
    bool operator !=(const LocalTransformComponent& other) const { return !(*this == other); }
};

struct WorldTransformComponent
{
    Core::Geometric::Transform transform;

    WorldTransformComponent() = default;
    WorldTransformComponent(const WorldTransformComponent&) = default;
    WorldTransformComponent(WorldTransformComponent&&) = default;
    WorldTransformComponent& operator=(const WorldTransformComponent&) = default;
    WorldTransformComponent& operator=(WorldTransformComponent&&) = default;

    WorldTransformComponent(const Core::Geometric::Transform& transform)
    : transform(transform)
    {}
    
    bool operator==(const WorldTransformComponent& other) const
    {
        return (transform == other.transform);
    }
    bool operator !=(const WorldTransformComponent& other) const { return !(*this == other); }
};
}// namespace Application