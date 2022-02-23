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
        bool HasComponent(const Entity& entity) { return _archetypes.HasComponent<T>(entity); }
        
        template <typename T>
        bool HasComponent(const EntityId& entity) { return _archetypes.HasComponent<T>(entity); }

        template <typename T>
        T& GetComponentFor(const Entity& entity) { return _archetypes.GetComponentFor<T>(entity); }

        template <typename T>
        T& GetComponentFor(const EntityId& entity) { return _archetypes.GetComponentFor<T>(entity); }

        template <typename ...Ts>
        void AddComponentsTo(Entity& entity) { _archetypes.AddComponentsTo<Ts...>(entity); }

        // must provide an argument for each component type provided
        template <typename ...Ts>
        void AddComponentsTo(Entity& entity, Ts&& ...args) { _archetypes.AddComponentsTo<Ts...>(entity, std::forward<Ts>(args)...); }

        template <typename ...Ts>
        void RemoveComponentsFrom(Entity& entity) { _archetypes.RemoveComponentsFrom(entity); }

        template <typename ...Ts>
        Entity CreateEntity() { return _archetypes.CreateEntity(); }

        Entity CreateEntity(const EntityCreator& creator) { return _archetypes.CreateEntity(creator); }
        /*
         NOTE: This consumes the calls when using anything (ex: above method)
            - either need to use different names, or just use the tuple constructor below (since we require constructed values anyways)
            - or we need to find a way for this to NOT consume other calls
        */
        // must provide an argument for each component type provided
        // template <typename ...Ts>
        // Entity CreateEntity(Ts&& ...args) { return _archetypes.CreateEntity<Ts...>(std::forward<Ts>(args)...); }
        
        template <typename ...Ts>
        Entity CreateEntity(const std::tuple<Ts...>& components) { return _archetypes.CreateEntity(components); }

        void RemoveEntity(const Entity& entity) { _archetypes.RemoveEntity(entity); }
        
        EntitySnapshot GetTemporaryEntitySnapshot(const Entity& entity) { return _archetypes.GetTemporaryEntitySnapshot(entity); }
        EntitySnapshot GetTemporaryEntitySnapshot(const EntityId& entity) { return _archetypes.GetTemporaryEntitySnapshot(entity); }

        void Update() { _systems.Update(); }

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddSystem(ARGS&& ...args) { return _systems.AddSystem<SYSTEM, ARGS...>(std::forward<ARGS>(args)...); }
        template <typename SYSTEM>
        void RemoveSystem() { _systems.RemoveSystem<SYSTEM>(); }

    private:
        ArchetypeManager _archetypes;
        SystemManager _systems;
    };
} // namespace Application