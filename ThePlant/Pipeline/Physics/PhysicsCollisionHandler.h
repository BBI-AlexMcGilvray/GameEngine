#pragma once

#include <vector>

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
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
    // notes:
    /*
    * https://www.nuclear-power.com/laws-of-conservation/law-of-conservation-of-energy/conservation-of-momentum-and-energy-in-collisions/
    * https://study.com/skill/learn/how-to-solve-for-the-final-velocity-of-an-elastic-1d-collision-explanation.html
    */
    void _Apply(const Core::Geometric::Point3D& collisionPoint, EntitySnapshot& from, EntitySnapshot& to) const override
    {
        Core::Ptr<VelocityComponent> fromVelocity = from.HasComponent<VelocityComponent>() ? &from.GetComponent<VelocityComponent>() : nullptr;
        const WorldTransformComponent& fromTransform = from.GetComponent<WorldTransformComponent>();
        const RigidBodyComponent& fromRigidBody = from.GetComponent<RigidBodyComponent>();

        VelocityComponent& toVelocity = to.GetComponent<VelocityComponent>();
        const WorldTransformComponent& toTransform = to.GetComponent<WorldTransformComponent>();
        const RigidBodyComponent& toRigidBody = to.GetComponent<RigidBodyComponent>();

        // lazy inelastic collisions: calculate elastic collision then multiply results by the conservation ratio
        const auto conservationRatio = fromRigidBody.elasticity * toRigidBody.elasticity;
        
        // the portion of the velocity that contributes to the 'head-on' collision is treated as a point collision, the rest is unaffected
        const auto toToCollision = collisionPoint - toTransform.transform.GetPosition();
        const auto toCollisionVelocity = Core::Math::Project(toVelocity.velocity, toToCollision);
        const auto toPersistingVelocity = toVelocity.velocity - toCollisionVelocity;

        /*
        * Seems like the reason this happens is because the toToCollision is 0 -> projection breaks -> velocity = NAN (which then propogates to breaking the position etc)
        *   This seems to be because of the explicit -1 multiplication below, so if the collision lasts multiple frames, it flips back and forth, and if it results in net-downward movement, eventually the distance is 0
        * for some reason they can get stuck together - probably due to the fact that we _may_ check intersection once they are already 'inside', causing them to intersect for multiple frames
        * and jitter back and forth as a result. probably need to provide the 'collision points' independent of each other (instead of the middle) so they each think they are bouncing off their edge
        */

        if (fromVelocity == nullptr)
        {
            // if we are bouncing away but still 'touching', just ignore
            if (Core::Math::Dot(toVelocity.velocity, toToCollision) < 0.0f)
            {
                return;
            }

            // from is not moving (immovable object) so the 'to' is just directly reflected
            toVelocity.velocity = toPersistingVelocity + (toCollisionVelocity * -1.0f * conservationRatio);
            if (conservationRatio == 1.0f)
            {
                const auto oldMagnitudeSqr = Core::Math::MagnitudeSqr(toCollisionVelocity + toPersistingVelocity);
                const auto newMagnitudeSqr = Core::Math::MagnitudeSqr(toVelocity.velocity);
                VERIFY(std::abs(oldMagnitudeSqr - newMagnitudeSqr) < 0.05f, "These should be equal (enough) but " + std::to_string(newMagnitudeSqr) + " != " + std::to_string(oldMagnitudeSqr));
            }
            if (toVelocity != toVelocity)
            {
                DEBUG_THROW("PhysicsCollisionHandler", "velocity is NAN");
            }
            return;
        }

        const auto fromToCollision = collisionPoint - fromTransform.transform.GetPosition();
        const auto fromCollisionVelocity = Core::Math::Project(fromVelocity->velocity, fromToCollision);
        const auto fromPersistingVelocity = fromVelocity->velocity - fromCollisionVelocity;

        /*
        * v2' = [(m1 * v1) + (v2 * [m2 - ([m1 / 2] * [1 + (m2 / m1)])])] / [m2 + ([m1 / 2] * [1 - (m2 / m1)])]
        * v1' = v2' + v2 - v1
        * 
        * using to = 2
        * and from = 1
        */
       
        // NOTE: we need to only use the portion of the velocity that is projected to the collision point and then add that to the rest
        const auto m1 = fromRigidBody.mass;
        const auto& v1 = fromCollisionVelocity;
        const auto m2 = toRigidBody.mass;
        const auto& v2 = toCollisionVelocity;
        const auto m2_over_m1 = m2 / m1;
        const auto numerator = (v1 * m1) + (v2 * (m2 - ((m1 / 2.0f) * (1 + m2_over_m1))));
        const auto denominator = m2 + ((m1 / 2.0f) * (1 - m2_over_m1));

        const auto v2Final = numerator / denominator;
        const auto v1Final = v2Final + v2 - v1;

        if (denominator == 0.0f)
        {
            DEBUG_THROW("PhysicsCollisionHandler", "Dividing by zero");
        }

        fromVelocity->velocity = fromPersistingVelocity + (v1Final * conservationRatio);
        toVelocity.velocity = toPersistingVelocity + (v2Final * conservationRatio);
    }
};
} // namespace Collision
}// namespace Application