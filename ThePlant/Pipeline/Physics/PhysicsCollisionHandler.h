#pragma once

#include <vector>

#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"

namespace Application
{
namespace Collision
{
struct RigidBodyCollision : public CollisionHandler<RigidBodyCollision>
{
    RigidBodyCollision()
    : CollisionHandler<RigidBodyCollision>("RigidBodyCollision", CollectTypes<VelocityComponent, RigidBodyComponent>(), CollectTypes<VelocityComponent, RigidBodyComponent>(), false)
    {} // don't need to handle both separately as this is an identical calculation

private:
    void _Apply(const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        const VelocityComponent& fromVelocity = from.GetComponent<VelocityComponent>();
        const RigidBodyComponent& fromRigidBody = from.GetComponent<RigidBodyComponent>();

        const VelocityComponent& toVelocity = to.GetComponent<VelocityComponent>();
        const RigidBodyComponent& toRigidBody = to.GetComponent<RigidBodyComponent>();

        const auto totalMass = fromRigidBody.mass + toRigidBody.mass;

        const auto fromEnergy = (fromVelocity.velocity * fromVelocity.velocity) * fromRigidBody.mass * 0.5f;
        const auto toEnergy = (toVelocity.velocity * toVelocity.velocity) * toRigidBody.mass * 0.5f;
        const auto totalEnergy = fromEnergy + toEnergy;
        const auto finalEnergy = totalEnergy * fromRigidBody.elasticity * toRigidBody.elasticity;

        // need to use these to determine the new direction (but how)
        const auto fromCollisionDirection = collisionPoint - fromPosition;
        const auto toCollisionDirection = collisionPoint - toPosition;

        fromVelocity.velocity *= Core::Math::Dot() * (totalEnergy * (fromRigidBody.mass / totalMass));
        toVelocity.velocity *= (totalEnergy * (toRigidBody.mass / totalMass));

        // This means we WILL need a 'point of contact' in the collision logic, so let's get that working
        fromVelocity.velocity = // get direction of collision and adjust velocity based on that
        toVelocity.velocity = // something similar
    }
};
} // namespace Collision
}// namespace Application