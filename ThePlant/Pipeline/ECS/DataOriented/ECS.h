#pragma once

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"
#include "Pipeline/ECS/DataOriented/Systems/SystemManager.h"

namespace Application
{
    // this is the only class that should be referenced externally, everything should go through this (but be handled by the ArchetypeManager and SystemManager)
    class ECS
    {
    public:
        ECS()
        : _systems(_archetypes)
        {}

        ECS(const ECS&) = delete;
        ECS(ECS&&) = delete;
        ECS& operator=(const ECS&) = delete;
        ECS& operator=(ECS&&) = delete;

        // we need all calls that ArchetypeManager and SystemManager have and forward to them respectively
        template <typename T>
        T& GetComponentFor(const Entity& entity) { return _archetypes.GetComponentFor<T>(entity); }

        template <typename ...Ts>
        void AddComponentsTo(Entity& entity) { _archetypes.AddComponentsTo<Ts...>(entity); }

        // must provide an argument for each component type provided
        template <typename ...Ts>
        void AddComponentsTo(Entity& entity, Ts&& ...args) { _archetypes.AddComponentsTo<Ts...>(entity, std::forward<Ts>(args)...); }

        template <typename ...Ts>
        void RemoveComponentsFrom(Entity& entity) { _archetypes.RemoveComponentsFrom(entity); }

        template <typename ...Ts>
        Entity CreateEntity() { return _archetypes.CreateEntity(); }

        // must provide an argument for each component type provided
        template <typename ...Ts>
        Entity CreateEntity(Ts&& ...args) { return _archetypes.CreateEntity<Ts...>(std::forward<Ts>(args)...); }
        
        template <typename ...Ts>
        Entity CreateEntity(const std::tuple<Ts...>& components) { return _archetypes.CreateEntity(components); }

        void RemoveEntity(const Entity& entity) { _archetypes.RemoveEntity(entity); }
        
        void Update() { _systems.Update(); }

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddSystem(ARGS&& ...args) { return _systems.AddSystem<SYSTEM, ARGS...>(std::forward<ARGS>(args)...); }

    private:
        ArchetypeManager _archetypes;
        SystemManager _systems;
    };
} // namespace Application