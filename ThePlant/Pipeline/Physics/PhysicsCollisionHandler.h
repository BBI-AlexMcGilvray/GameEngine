#pragma once

#include <vector>

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"

namespace Application
{
namespace Collision
{
// we are only handling collisions very simply
// ex: we do not apply rotation, and we treast annd shapes as if they were spheres
struct RigidBodyCollision : public CollisionHandler<RigidBodyCollision>
{
    RigidBodyCollision()
    : CollisionHandler<RigidBodyCollision>("RigidBodyCollision", CollectTypes<WorldTransformComponent, RigidBodyComponent>(), CollectTypes<VelocityComponent, WorldTransformComponent, RigidBodyComponent>(), false)
    {} // don't need to handle both separately as this is an identical calculation

private:
    void _Apply(const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        Core::Ptr<VelocityComponent> fromVelocity = from.HasComponent<VelocityComponent>() ? &from.GetComponent<VelocityComponent>() : nullptr;
        const WorldTransformComponent& fromTransform = from.GetComponent<WorldTransformComponent>();
        const RigidBodyComponent& fromRigidBody = from.GetComponent<RigidBodyComponent>();

        VelocityComponent& toVelocity = to.GetComponent<VelocityComponent>();
        const WorldTransformComponent& toTransform = to.GetComponent<WorldTransformComponent>();
        const RigidBodyComponent& toRigidBody = to.GetComponent<RigidBodyComponent>();

        const auto totalMass = fromRigidBody.mass + toRigidBody.mass;

        const auto fromEnergy = Core::Math::sqr(fromVelocity != nullptr ? fromVelocity->velocity : 0.0f) * fromRigidBody.mass * 0.5f;
        const auto toEnergy = (toVelocity.velocity * toVelocity.velocity) * toRigidBody.mass * 0.5f;
        const auto totalEnergy = fromEnergy + toEnergy;
        const auto finalEnergy = totalEnergy * fromRigidBody.elasticity * toRigidBody.elasticity;

        // need to use these to determine the new direction (but how)
        const auto fromCollisionDirection = collisionPoint - fromTransform.transform.GetPosition();
        const auto toCollisionDirection = collisionPoint - toTransform.transform.GetPosition();

        Core::Math::Float3 netCollisionVelocity = toToContact + fromToContact; // we only need to 'balance' the direct-collision velocity. but how?

        // the premise below is that the velocity 'parallel' to the contact plane (defined the the normal) is not affected
        // only the velocity 'perpendicular' to the plane is affected
        // but the below does not take into account 'additive' velocity/etc
        // also, should friction be taken into account momentarily? probably not...
        if (fromVelocity != nullptr)
        {
            const auto fromToContact = Core::Math::Project(fromVelocity->velocity, fromCollisionDirection);
            const auto fromAlongContact = fromVelocity->velocity - fromToContact;
            const auto fromFinalVelocity = fromAlongContact - (fromToContact * fromRigidBody.elasticity * toRigidBody.elasticity);
            fromVelocity->velocity = fromFinalVelocity;
        }

        const auto toToContact = Core::Math::Project(toVelocity.velocity, toCollisionDirection);
        const auto toAlongContact = toVelocity.velocity - toToContact;
        const auto toFinalVelocity = toAlongContact - (toToContact * fromRigidBody.elasticity * toRigidBody.elasticity);
        toVelocity.velocity = toFinalVelocity * (toRigidBody.mass / totalMass);
    }
};
} // namespace Collision
}// namespace Application