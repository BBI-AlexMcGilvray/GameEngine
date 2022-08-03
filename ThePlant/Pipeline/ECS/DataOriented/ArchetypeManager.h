#pragma once

#include <utility>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/ECS/DataOriented/Archetype.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application {
class ArchetypeManager
{
public:
    ArchetypeManager() = default;
    ArchetypeManager(const ArchetypeManager&) = delete;
    ArchetypeManager(ArchetypeManager&&) = delete;
    ArchetypeManager& operator=(const ArchetypeManager&) = delete;
    ArchetypeManager& operator=(ArchetypeManager&&) = delete;

    bool EntityExists(const EntityId& entity);

    template <typename T>
    bool HasComponent(const Entity& entity)
    {
        return _GetArchetype(entity.GetArchetypeId()).HasComponent<T>();
    }
    
    template <typename T>
    bool HasComponent(const EntityId& entity)
    {
        return _GetArchetype(entity).HasComponent<T>();
    }

    template <typename T>
    T& GetComponentFor(const Entity& entity)
    {
        return _GetArchetype(entity.GetArchetypeId()).GetComponentFor<T>(entity.GetEntityId());
    }

    template <typename T>
    T& GetComponentFor(const EntityId& entity)
    {
        return _GetArchetype(entity).GetComponentFor<T>(entity);
    }
        
    // if multiple components are to be accessed for an entity, this is better that calling the above for each component
    EntitySnapshot GetTemporaryEntitySnapshot(const Entity& entity);
    EntitySnapshot GetTemporaryEntitySnapshot(const EntityId& entity);

    // returning handler for easy chaining and efficiency
    template <typename T, typename ...ARGS>
    EntityHandler& AddComponent(const EntityId& entity, ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        EntityHandler& handler = _GetEntityHandler(entity, EntityState::Existing);

        handler.AddComponent<T>(std::forward<ARGS>(args)...);

        return handler;
    }

    template <typename T>
    EntityHandler& RemoveComponent(const EntityId& entity)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        EntityHandler& handler = _GetEntityHandler(entity, EntityState::Existing);

        handler.RemoveComponent<T>();

        return handler;
    }

    // ArchetypeManager is in charge of creating new entity ids now
    EntityHandler& CreateEntity()
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        EntityHandler& handler = _GetEntityHandler(Core::GetInstanceId<EntityId>(), EntityState::New);

        return handler;
    }

    // no reference return to enforce the paradigm where if an entity is removed, nothing else should happen to it
    // still possible for other changes to be queued, but they should be queued in ignorance of it being deleted
    void RemoveEntity(const EntityId& entity)
    {
        _GetEntityHandler(entity, EntityState::Existing).DeleteEntity();
    }

    void ApplyChanges();

    template <typename ...Ts>
    std::vector<Core::Ptr<Archetype>> GetArchetypesContaining()
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        TypeCollection types = CollectTypes<Ts...>();

        std::vector<Core::Ptr<Archetype>> relevantArchetypes;

        for (auto& archetype : _archetypes)
        {
            if (archetype.ContainsTypes(types))
            {
                relevantArchetypes.emplace_back(&archetype);
            }
        }

        return relevantArchetypes;
    }

    // potential optimization: ForEachArchetypeContaining(METHOD) to avoid multiple pointer indirections and vector sizing/creation

private:
    enum class EntityState
    {
        New,
        Existing
    };

    std::vector<Archetype> _archetypes;
    std::unordered_map<EntityId, EntityHandler> _entityChanges;

    template <typename ...Ts>
    bool _HasArchetype()
    {
        TypeCollection types = CollectTypes<Ts...>();

        return _HasArchetype(types);
    }
    bool _HasArchetype(const TypeCollection& archetypeTypes) const;
    bool _HasArchetype(const ArchetypeId& archetypeId) const;

    template <typename ...Ts>
    Archetype& _GetArchetype()
    {
        TypeCollection types = CollectTypes<Ts...>();

        return _GetArchetype(types);
    }
    Archetype& _GetArchetype(const TypeCollection& archetypeTypes);
    Archetype& _GetArchetype(const ArchetypeId& archetypeId);
    Archetype& _GetArchetype(const EntityId& entity);

    void _CreateEntityHandler(const EntityId& entity, EntityState state);
    EntityHandler& _GetEntityHandler(const EntityId& entity, EntityState state);

    // methods for ACTUALLY doing the entity changes
    void _ApplyHandler(const EntityHandler& handler);
    void _RemoveEntity(const EntityId& entity);
};
}// namespace Application