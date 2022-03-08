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
    : CollisionHandler<RigidBodyCollision>("RigidBodyCollision", CollectTypes<WorldTransformComponent, RigidBodyComponent>(), CollectTypes<VelocityComponent, WorldTransformComponent, RigidBodyComponent>(), false)
    {} // don't need to handle both separately as this is an identical calculation

private:
    void _Apply(const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        Core::Ptr<const VelocityComponent> fromVelocity = from.HasComponent<VelocityComponent>() ? &from.GetComponent<VelocityComponent>() : nullptr;
        const WorldTransformComponent& fromTransform = from.GetComponent<WorldTransformComponent>();
        const RigidBodyComponent& fromRigidBody = from.GetComponent<RigidBodyComponent>();

        const VelocityComponent& toVelocity = to.GetComponent<VelocityComponent>();
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

        if (fromVelocity != nullptr)
        {
            fromVelocity->velocity *= Core::Math::Dot() * (totalEnergy * (fromRigidBody.mass / totalMass));
        }
        toVelocity.velocity *= (totalEnergy * (toRigidBody.mass / totalMass));
    }
};
} // namespace Collision
}// namespace Application