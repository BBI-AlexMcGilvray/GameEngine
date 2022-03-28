#pragma once

#include <set>
#include <tuple>

#include "Materials/Core/IdTypes/RuntimeId.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/Time/Headers/TimeManager.h"

namespace Application {
// holds boiler plate code that is the same for all systems before forwarding to the specific handling for the system
// is this how other (future) system types would be handled? what about custom system types defined by products?
//      - may be going to deep, one step at a time, handle the situations as they arrise
struct IDeltaTimeSystem : public ISystem
{
    IDeltaTimeSystem(const std::string& name, const Time::TimeManager& timeManager)
    : ISystem(name)
    , _timeManager(timeManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const final
    {
        DeltaTimeExecute(_timeManager.GetDeltaTime(), archetypeManager);
    }

    virtual void DeltaTimeExecute(const Core::Second& time, ArchetypeManager& archetypeManager) const = 0;

private:
    const Time::TimeManager& _timeManager;
};

template <typename SYSTEM, typename ...Ts>
struct DeltaTimeSystem : public IDeltaTimeSystem
{
    DeltaTimeSystem(const std::string& name, const Time::TimeManager& timeManager)
    : IDeltaTimeSystem(name, timeManager)
    {}

    void DeltaTimeExecute(const Core::Second& time, ArchetypeManager& archetypeManager) const override
    {
        std::vector<Archetype*> affectedArchetypes = _archetypeManager.GetArchetypesContaining<Ts...>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(time, archetype);
        }
    }

private:
    void _ApplyToArchetype(const Core::Second& time, Core::Ptr<Archetype> archetype) const
    {
        SYSTEM::ApplyToArchetype(time, archetype->GetComponents<Ts>()...);
    }
};

template <typename SYSTEM>
struct DeltaTimeSystem<SYSTEM> : public IDeltaTimeSystem
{
    using ISystem::ISystem;

    DeltaTimeSystem(const std::string& name, Time::TimeManager& timeManager)
    : IDeltaTimeSystem(name, timeManager)
    {}

    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    // no archetypes means the system must provide it's own DeltaTimeExecute method
};

template <typename SYSTEM, typename ...NESTED>
struct CompoundDeltaTimeSystem : public IDeltaTimeSystem
{
    using ISystem::ISystem;

    CompoundDeltaTimeSystem(const std::string& name, Time::TimeManager& timeManager)
    : IDeltaTimeSystem(name, timeManager)
    {}

    template <typename ...ARGS>
    CompoundDeltaTimeSystem(const std::string& name, Time::TimeManager& timeManager, ARGS&& ...args)
    : IDeltaTimeSystem(name, timeManager)
    , _nestedSystems({timeManager, std::forward<ARGS>(args)}, ...) // this may not work if the nested systems have constructors with more than 1 argument (or if not all types are provided an argument)
    {}

    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    // this works for now, but the nested systems won't be parallelized in the future without changes
    // could just change the internal call to execute each as a task (with the same dependencies as the main system)
    void DeltaTimeExecute(const Core::Second& time,ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::apply([&archetypeManager](const auto& ...args)
        {
            // all tuple elements are passed as arguemnts, hence the expression expansion logic
            (args.DeltaTimeExecute(time, archetypeManager), ...);
        }, _nestedSystems);
    }

private:
    std::tuple<NESTED...> _nestedSystems;
};
}// namespace Application
