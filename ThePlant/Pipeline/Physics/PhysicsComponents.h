#pragma once

#include <variant>

#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application
{
struct VelocityComponent
{
    Core::Math::Float3 velocity;

    VelocityComponent() = default;
    VelocityComponent(const VelocityComponent&) = default;
    VelocityComponent(VelocityComponent&&) = default;
    VelocityComponent& operator=(const VelocityComponent&) = default;
    VelocityComponent& operator=(VelocityComponent&&) = default;

    VelocityComponent(const float& velocity)
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
    float gravityRatio = 1.0f;

    PhysicsComponent() = default;
    PhysicsComponent(const PhysicsComponent&) = default;
    PhysicsComponent(PhysicsComponent&&) = default;
    PhysicsComponent& operator=(const PhysicsComponent&) = default;
    PhysicsComponent& operator=(PhysicsComponent&&) = default;

    PhysicsComponent(const float& gravityRatio)
    : gravityRatio(gravityRatio)
    {}

    bool operator==(const PhysicsComponent& other) const
    {
        return gravityRatio == other.gravityRatio;
    }
    bool operator !=(const PhysicsComponent& other) const { return !(*this == other); }
};

// used to treat as a 'physical' object
struct RigidBodyComponent
{
    float elasticity = 0.0;
    float friction = 0.5f; // when on surface
    float drag = 0.5f; // always
    float mass = 1.0f;

    RigidBodyComponent() = default;
    RigidBodyComponent(const RigidBodyComponent&) = default;
    RigidBodyComponent(RigidBodyComponent&&) = default;
    RigidBodyComponent& operator=(const RigidBodyComponent&) = default;
    RigidBodyComponent& operator=(RigidBodyComponent&&) = default;

    RigidBodyComponent(const float& elasticity, const float& friction, const float& drag)
    : elasticity(elasticity)
    , friction(friction)
    , drag(drag)
    {}

    bool operator==(const RigidBodyComponent& other) const
    {
        return elasticity == other.elasticity && friction == other.friction && drag == other.drag;
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