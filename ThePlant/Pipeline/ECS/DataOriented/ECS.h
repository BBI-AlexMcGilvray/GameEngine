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
        
        // if multiple components are to be accessed for an entity, this is better that calling the above for each component   
        EntitySnapshot GetTemporaryEntitySnapshot(const Entity& entity) { return _archetypes.GetTemporaryEntitySnapshot(entity); }
        EntitySnapshot GetTemporaryEntitySnapshot(const EntityId& entity) { return _archetypes.GetTemporaryEntitySnapshot(entity); }

        template <typename T, typename ...ARGS>
        EntityHandler& AddComponent(const EntityId& entity, ARGS&& ...args) { return _archetypes.AddComponent<T>(std::forward<ARGS>(args)...); }

        template <typename T>
        EntityHandler& RemoveComponent(const EntityId& entity) { return _archetypes.RemoveComponent<T>(); }

        EntityHandler& CreateEntity() { return _archetypes.CreateEntity(); }

        void RemoveEntity(const EntityId& entity) { return _archetypes.RemoveEntity(entity); }

        void Update() { _systems.Update(); }

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddSystem(ARGS&& ...args) { return _systems.AddSystem<SYSTEM, ARGS...>(std::forward<ARGS>(args)...); }
        template <typename SYSTEM>
        void RemoveSystem() { _systems.RemoveSystem<SYSTEM>(); }
        
    #if DEBUG
        std::vector<Core::Ptr<ISystem>> GetCurrentSystems() { return _systems.GetCurrentSystems(); }
    #endif

    private:
        ArchetypeManager _archetypes;
        SystemManager _systems;
    };
} // namespace Application