#pragma once

#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Debugging/Profiling/Utils.h"
#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Pipeline/ECS/DataOriented/Systems/DeltaTimeSystem.h"

#include "Pipeline/Physics/PhysicsComponents.h"
#include "Pipeline/Physics/PhysicsSettings.h"

namespace Application {
struct PhysicsSystem : public DeltaTimeSystem<PhysicsSystem>
{
    PhysicsSystem(const Time::TimeSystem& timeSystem, Physics::Settings& physicsSettings)
    : DeltaTimeSystem<PhysicsSystem>("PhysicsSystem", timeSystem)
    , _physicsSettings(physicsSettings)
    {}

    // ideally this (taking a delta time parameter) is handled by the base class so we can rest easy knowing they all get it from the same place
    // but how? make a separate type of 'system' class that requires a delta time parameter that is provided by the ECS system?
    // this means ECS (and System) types must take in a reference to the game's time manager
    // is this how other (future) system types would be handled? what about custom system types defined by products?
    //      - may be going to deep, one step at a time, handle the situations as they arrise
    void DeltaTimeExecute(const Core::Second& deltaTime, ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());
        
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<PhysicsComponent, VelocityComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(deltaTime, _physicsSettings, *archetype);
        }
    }

private:
    const Physics::Settings& _physicsSettings;
    
    // need this to ensure none of the affected archetypes have a CameraWeightingComponent
    static void _ApplyToArchetype(const Core::Second& deltaTime, const Physics::Settings& physicsSettings, Archetype& archetype)
    {
        std::vector<PhysicsComponent>& physics = archetype.GetComponents<PhysicsComponent>();
        std::vector<VelocityComponent>& velocities = archetype.GetComponents<VelocityComponent>();
        Core::Ptr<std::vector<RigidBodyComponent>> rigidBodies = archetype.HasComponent<RigidBodyComponent>() ? &(archetype.GetComponents<RigidBodyComponent>()) : nullptr;

        DEBUG_ASSERT(physics.size() == velocities.size());
        for (size_t index = 0; index < physics.size(); ++index)
        {
            PhysicsComponent& physicsComponent = physics[index];
            VelocityComponent& velocityComponent = velocities[index];

            auto additionalVelocity = physicsSettings.gravity * (physicsComponent.gravityRatio * static_cast<float>(Core::Duration(deltaTime)));
            if (rigidBodies != nullptr)
            {
                additionalVelocity *= (1.0f - (*rigidBodies)[index].drag);
            }

            velocityComponent.velocity += additionalVelocity;

            // not the most 'realistic', but trying to not make it super expensive
            Core::Math::Float3 signs = { velocityComponent.velocity.X >= 0.0f ? 1.0f : -1.0f, velocityComponent.velocity.Y >= 0.0f ? 1.0f : -1.0f, velocityComponent.velocity.Z >= 0.0f ? 1.0f : -1.0f };
            velocityComponent.velocity = Core::Math::Min(Core::Math::Abs(velocityComponent.velocity), std::abs(physicsComponent.maxVelocity)); // cap out each direction separately
            velocityComponent.velocity *= signs;
        }
    }
};
} // namespace Application