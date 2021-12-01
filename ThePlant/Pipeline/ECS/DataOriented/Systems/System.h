#pragma once

#include "ArchetypeManager.h"

namespace Application {
struct ISystem
{
    template <typename T>
    bool IsSystem() { return (GetTypeId<T> == GetSystem()); }
    virtual runtimeId_t GetSystem() const = 0;
    virtual void Execute(const ArchetypeManager& archetypeManager) const = 0;
};

// holds boiler plate code that is the same for all systems before forwarding to the specific handling for the system
template <typename SYSTEM, typename ...Ts>
struct System : public ISystem
{
    runtimeId_t GetSystem() const override
    {
        return GetTypeId<SYSTEM>();
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
