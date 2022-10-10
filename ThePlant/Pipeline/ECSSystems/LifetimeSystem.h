#pragma once

#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/ECS/DataOriented/Systems/DeltaTimeSystem.h"

#include "Pipeline/ECSSystems/LifetimeComponent.h"

namespace Application {
struct LifetimeSystem : public DeltaTimeSystem<LifetimeSystem>
{
    LifetimeSystem(const Time::TimeSystem& timeSystem)
    : DeltaTimeSystem<LifetimeSystem>(timeSystem)
    {}

    void DeltaTimeExecute(const Core::Second& time, ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<LifetimeComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(time, archetypeManager, *archetype);
        }
    }

private:
    // need this to ensure none of the affected archetypes have a CameraWeightingComponent
    static void _ApplyToArchetype(const Core::Second& deltaTime, ArchetypeManager& archetypeManager, Archetype& archetype)
    {
        float dt = Core::Duration(deltaTime);

        const std::vector<EntityId>& entities = archetype.GetEntities();
        std::vector<LifetimeComponent>& lifetimes = archetype.GetComponents<LifetimeComponent>();

        size_t index = 0;
        for (LifetimeComponent& lifetime : lifetimes)
        {
            lifetime.lifetime -= dt;

            if (lifetime.lifetime <= 0.0f)
            {
                archetypeManager.RemoveEntity(entities[index]);
            }
            ++index;
        }
    }
};
} // namespace Application