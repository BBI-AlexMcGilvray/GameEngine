#pragma once

#include "ArchetypeManager.h"

struct ISystem
{
    ISystem(ArchetypeManager& archetypeManager)
    : _archetypeManager(archetypeManager)
    {}

    virtual void Execute() = 0;

public:
    ArchetypeManager& _archetypeManager;
};

// holds boiler plate code that is the same for all systems before forwarding to the specific handling for the system
template <typename SYSTEM, typename ...Ts>
struct System : public ISystem
{
    System(ArchetypeManager& archetypeManager)
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
