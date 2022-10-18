#pragma once

#include <variant>

#include "Core/Reflection/Reflectable.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application
{
struct VelocityComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Core::Math::Float3 velocity;

    VelocityComponent() = default;
    VelocityComponent(const VelocityComponent&) = default;
    VelocityComponent(VelocityComponent&&) = default;
    VelocityComponent& operator=(const VelocityComponent&) = default;
    VelocityComponent& operator=(VelocityComponent&&) = default;

    VelocityComponent(const Core::Math::Float3& velocity)
    : velocity(velocity)
    {}

    bool operator==(const VelocityComponent& other) const
    {
        return velocity == other.velocity;
    }
    bool operator !=(const VelocityComponent& other) const { return !(*this == other); }
};

// not using an acceleration component at the moment, keeping it simple
// plus, how would that play with different accelerations? clear them all then set each frame? gross, deal with it if needed

// used to denote it respects physics
struct PhysicsComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    float gravityRatio = 1.0f;
    float maxVelocity = 100.0f;

    PhysicsComponent() = default;
    PhysicsComponent(const PhysicsComponent&) = default;
    PhysicsComponent(PhysicsComponent&&) = default;
    PhysicsComponent& operator=(const PhysicsComponent&) = default;
    PhysicsComponent& operator=(PhysicsComponent&&) = default;

    PhysicsComponent(const float& gravityRatio, const float& maxVelocity)
    : gravityRatio(gravityRatio)
    , maxVelocity(maxVelocity)
    {}

    bool operator==(const PhysicsComponent& other) const
    {
        return gravityRatio == other.gravityRatio && maxVelocity == other.maxVelocity;
    }
    bool operator !=(const PhysicsComponent& other) const { return !(*this == other); }
};

// used to treat as a 'physical' object
struct RigidBodyComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    float elasticity = 0.0; // [0, 1]
    float friction = 0.5f; // when on surface

    // always
    float drag = 0.5f; // [0, 1]
    float mass = 1.0f;

    RigidBodyComponent() = default;
    RigidBodyComponent(const RigidBodyComponent&) = default;
    RigidBodyComponent(RigidBodyComponent&&) = default;
    RigidBodyComponent& operator=(const RigidBodyComponent&) = default;
    RigidBodyComponent& operator=(RigidBodyComponent&&) = default;

    RigidBodyComponent(const float& elasticity, const float& friction, const float& drag, const float& mass)
    : elasticity(elasticity)
    , friction(friction)
    , drag(drag)
    , mass(mass)
    {}

    bool operator==(const RigidBodyComponent& other) const
    {
        return elasticity == other.elasticity && friction == other.friction && drag == other.drag && mass == other.mass;
    }
    bool operator !=(const RigidBodyComponent& other) const { return !(*this == other); }
};

// types of connections
namespace Connection
{
    struct Rigid
    {
        float length;
        Core::Math::FQuaternion angle;
    };

    struct Pendulum
    {
        float length;
    };

    struct Spring
    {
        float minimumLenght;
        float springConstant;
    };
}

using ConnectionType = std::variant<Connection::Rigid, Connection::Pendulum, Connection::Spring>;

struct ConnectionComponent
{
    ConnectionType connection;
    EntityId otherEntity;
};
} // namespace Application