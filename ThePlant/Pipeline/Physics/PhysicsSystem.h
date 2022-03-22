#pragma once

#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/ECS/DataOriented/Systems/System.h"

#include "Pipeline/Physics/PhysicsComponents.h"
#include "Pipeline/Physics/PhysicsSettings.h"

namespace Application {
struct PhysicsSystem : public TimeSystem<PhysicsSystem>
{
    PhysicsSystem(const Physics::Settings& physicsSettings)
    : TimeSystem<PhysicsSystem>("PhysicsSystem")
    , _physicsSettings(physicsSettings)
    {}

    // ideally this (taking a delta time parameter) is handled by the base class so we can rest easy knowing they all get it from the same place
    // but how? make a separate type of 'system' class that requires a delta time parameter that is provided by the ECS system?
    // this means ECS (and System) types must take in a reference to the game's time manager
    // is this how other (future) system types would be handled? what about custom system types defined by products?
    //      - may be going to deep, one step at a time, handle the situations as they arrise
    void Execute(const Core::Second& deltaTime, ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());
        
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<PhysicsComponent, VelocityComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(deltaTime, _physicsSettings, archetype->GetComponents<PhysicsComponent>(), archetype->GetComponents<VelocityComponent>());
        }
    }

private:
    const Physics::Settings& _physicsSettings;
    
    // need this to ensure none of the affected archetypes have a CameraWeightingComponent
    static void _ApplyToArchetype(const Core::Second& deltaTime, const Physics::Settings& physicsSettings, std::vector<PhysicsComponent>& physics, std::vector<VelocityComponent>& velocities)
    {
        DEBUG_ASSERT(physics.size() == velocities.size());
        for (size_t index = 0; index < physics.size(); ++index)
        {
            const auto additionalVelocity = physics[index].gravityRatio * physicsSettings.gravity * Core::Duration(deltaTime);
            if (hasRigidBody)
            {
                additionalVelocity *= RigidBodyComponent.drag;
            }

            velocities[index].velocity += additionalVelocity;
        }
    }
};
} // namespace Application