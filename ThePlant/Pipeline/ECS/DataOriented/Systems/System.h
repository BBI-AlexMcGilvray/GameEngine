#pragma once

#include <set>
#include <tuple>

#include "Materials/Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"

namespace Application {
struct ISystem
{
    template <typename T>
    bool IsSystem() { return (Core::GetTypeId<T> == GetSystem()); }
    virtual Core::runtimeId_t GetSystem() const = 0;
    virtual void Execute(const ArchetypeManager& archetypeManager) const = 0;
    
    template <typename ...Ts>
    void AddDependency()
    {
        (AddDependency<Ts>(),...);
    }

    template <typename T>
    void AddDependency()
    {
        _dependencies.emplace(Core::GetTypeId<T>());
    }

    const std::set<Core::runtimeId_t>& GetDependencies() const { return _dependencies; }

private:
    std::set<Core::runtimeId_t> _dependencies;
};

// holds boiler plate code that is the same for all systems before forwarding to the specific handling for the system
template <typename SYSTEM, typename ...Ts>
struct System : public ISystem
{
    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    void Execute(const ArchetypeManager& archetypeManager) const override
    {
        std::vector<Archetype*> affectedArchetypes = archetypeManager.GetArchetypesContaining<Ts...>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype);
        }
    }

private:
    void _ApplyToArchetype(Archetype* archetype)
    {
        SYSTEM::ApplyToArchetype(archetype->GetComponents<Ts>()...);
    }
};

template <typename SYSTEM, typename ...NESTED>
struct CompoundSystem : public ISytem
{
    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    // this works for now, but the nested systems won't be parallelized in the future without changes
    // could just change the internal call to execute each as a task (with the same dependencies as the main system)
    void Execute(const ArchetypeManager& archetypeManager) const override
    {
        std::apply([](const auto& ...args)
        {
            // all tuple elements are passed as arguemnts, hence the expression expansion logic
            (args.Execute(archetypeManager), ...);
        }, _nestedSystems);
    }

private:
    std::tuple<NESTED...> _nestedSystems;
};

/*
template <typename SYSTEM, typename ...Ts>
struct DeltaTimeSystem : public ISystem
{
    DeltaTimeSystem(ArchetypeManager& archetypeManager, TimeManager& timeManager)
    : ISystem(archetypeManager)
    {}

    void Execute()
    {
        std::vector<Archetype*> affectedArchetypes = _archetypeManager.GetArchetypesContaining<Ts...>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype);
        }
    }

private:
    TimeManager& _timeManager;
    
    void _ApplyToArchetype(Archetype* archetype)
    {
        SYSTEM::_ApplyToArchetype(archetype, _timeManager.GetDeltaTime());
    }
};
*/
}// namespace Application
