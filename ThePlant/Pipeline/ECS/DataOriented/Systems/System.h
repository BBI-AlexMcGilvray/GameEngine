#pragma once

#include <set>
#include <tuple>

#include "Materials/Core/IdTypes/RuntimeId.h"

#include "Core/Debugging/Profiling/Utils.h"
#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"

namespace Application {
struct ISystem
{
    ISystem(const std::string& name)
    : _name(name)
    {}

    // may need to allow move constructors?
    ISystem(const ISystem&) = delete;
    ISystem(ISystem&&) = delete;
    ISystem& operator=(const ISystem&) = delete;
    ISystem& operator=(ISystem&&) = delete;

    const std::string& GetSystemName() const { return _name; }

    template <typename T>
    bool IsSystem() const { return (Core::GetTypeId<T>() == GetSystem()); }
    virtual Core::runtimeId_t GetSystem() const = 0;
    virtual void Execute(ArchetypeManager& archetypeManager) const = 0;
    
    template <typename ...Ts>
    ISystem& AddDependencies()
    {
        (AddDependency<Ts>(),...);
        return *this;
    }

    template <typename T>
    ISystem& AddDependency()
    {
        _dependencies.emplace(Core::GetTypeId<T>());
        return *this;
    }

    ISystem& AddDependency()
    {
        return *this;
    }

    const std::set<Core::runtimeId_t>& GetDependencies() const { return _dependencies; }

private:
    const std::string _name;
    std::set<Core::runtimeId_t> _dependencies;
};

// holds boiler plate code that is the same for all systems before forwarding to the specific handling for the system
template <typename SYSTEM, typename ...Ts>
struct System : public ISystem
{
    using ISystem::ISystem;

    System(const std::string& name)
    : ISystem(name)
    {}

    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<Ts...>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype);
        }
    }

private:
    void _ApplyToArchetype(Core::Ptr<Archetype> archetype) const
    {
        SYSTEM::ApplyToArchetype(archetype->GetComponents<Ts>()...);
    }
};

template <typename SYSTEM>
struct System<SYSTEM> : public ISystem
{
    using ISystem::ISystem;

    System(const std::string& name)
    : ISystem(name)
    {}

    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    // no archetypes means the system must provide it's own Execute method
};

template <typename SYSTEM, typename ...NESTED>
struct CompoundSystem : public ISystem
{
    using ISystem::ISystem;

    CompoundSystem(const std::string& name)
    : ISystem(name)
    {}

    template <typename ...ARGS>
    CompoundSystem(const std::string& name, ARGS&& ...args)
    : ISystem(name)
    , _nestedSystems(std::forward<ARGS>(args)...)
    {}

    Core::runtimeId_t GetSystem() const override
    {
        return Core::GetTypeId<SYSTEM>();
    }

    // this works for now, but the nested systems won't be parallelized in the future without changes
    // could just change the internal call to execute each as a task (with the same dependencies as the main system)
    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::apply([&archetypeManager](const auto& ...args)
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
