#pragma once

#include "Core/Reflection/Reflectable.h"

#include "Materials/Core/Geometric/Transform.h"
#include "Materials/Core/Math/Headers/Quaternion.h"
#include "Materials/Core/Math/Headers/Vector3.h"

namespace Application {
struct PositionComponent
{
    // should be enough to get serialization and display data for free
    //      - a new visitor would be needed to make the display UI dynamically
    REFLECTABLE(
        (Core::Math::Float3)position
    )

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
    REFLECTABLE(
        (Core::Math::Float3)scale
    )

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
    REFLECTABLE(
        (Core::Math::FQuaternion)rotation
    )

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
    NOTHING_REFLECTABLE()
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

#define TEST_MACRO(...) #__VA_ARGS__
struct WorldTransformComponent
{
    NOTHING_REFLECTABLE()
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