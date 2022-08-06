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
        , _changeSyncSystems(_archetypes)
        {}

        ECS(const ECS&) = delete;
        ECS(ECS&&) = delete;
        ECS& operator=(const ECS&) = delete;
        ECS& operator=(ECS&&) = delete;

        bool EntityExists(const EntityId& entity) { return _archetypes.EntityExists(entity); }

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
        EntityHandler& RemoveComponent(const EntityId& entity) { return _archetypes.RemoveComponent<T>(entity); }

        EntityHandler& CreateEntity() { return _archetypes.CreateEntity(); }

        void RemoveEntity(const EntityId& entity) { return _archetypes.RemoveEntity(entity); }

        void ApplyChanges() { _archetypes.ApplyChanges(); }
        void Update()
        {
            // we do the first update to remove the need for safety checking inside systems, everything should be up-to-date once systems are run
            // maybe profile to verify this is faster, but doing 1 additional set of (rare) changes should be faster than all the safety checks otherwise required
            _changeSyncSystems.Update();
            _archetypes.ApplyChanges(); // handle changes made outside of ECS systems
            _systems.Update();
            _changeSyncSystems.Update();
            _archetypes.ApplyChanges(); // handle changes made by ECS systems
        }

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddSystem(ARGS&& ...args) { return _systems.AddSystem<SYSTEM, ARGS...>(std::forward<ARGS>(args)...); }
        template <typename SYSTEM>
        void RemoveSystem() { _systems.RemoveSystem<SYSTEM>(); }

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddChangeSyncSystem(ARGS&& ...args) { return _changeSyncSystems.AddSystem<SYSTEM, ARGS...>(std::forward<ARGS>(args)...); }
        template <typename SYSTEM>
        void RemoveChangeSyncSystem() { _changeSyncSystems.RemoveSystem<SYSTEM>(); }
        
    #if DEBUG
        std::vector<Core::Ptr<ISystem>> GetCurrentSystems() { return _systems.GetCurrentSystems(); }
        std::vector<Core::Ptr<ISystem>> GetCurrentChangeSyncSystems() { return _changeSyncSystems.GetCurrentSystems(); }
    #endif

    private:
        ArchetypeManager _archetypes;
        SystemManager _systems;
        SystemManager _changeSyncSystems;
    };
} // namespace Application