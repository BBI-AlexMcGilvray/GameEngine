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

    // NOTE: these should also all return a reference (to the entity handler(?) to allow chaining)
    // need a way for this to take in a value for the new components
    template <typename ...Ts>
    void AddComponentsTo(Entity& entity)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = AddToCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Add<Ts...>(oldArchetype));
        }
        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity.GetEntityId(), newArchetype);
    }

    // must provide an argument for each component type provided
    template <typename ...Ts>
    void AddComponentsTo(Entity& entity, Ts&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = AddToCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Add<Ts...>(oldArchetype));
        }

        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity.GetEntityId(), newArchetype);

        newArchetype.SetComponentFor(entity.GetEntityId(), std::forward<Ts>(args)...);
    }

    template <typename ...Ts>
    void RemoveComponentsFrom(Entity& entity)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = RemoveFromCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Remove<Ts...>(oldArchetype));
        }
        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity.GetEntityId(), newArchetype);
    }

    // create entity
    template <typename ...Ts>
    EntityId CreateEntity()
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        if (!_HasArchetype<Ts...>())
        {
            _archetypes.emplace_back(CreateArchetype<Ts...>());
            return _GetArchetype<Ts...>().AddEntity();
        }

        return _GetArchetype<Ts...>().AddEntity();
    }

    // this should queue the handler (and check that the associated entity and archetype are not set)
    // they should also return the EntityHandler so more updates can be made this frame? EntityId return is mandatory though
    EntityId CreateEntity(const EntityHandler& creator);

    /*
        NOTE: This consumes the calls when using anything (ex: above method)
        - either need to use different names, or just use the tuple constructor below (since we require constructed values anyways)
        - or we need to find a way for this to NOT consume other calls
    */
    // must provide an argument for each component type provided
    // template <typename ...Ts>
    // Entity CreateEntity(Ts&& ...args)
    // {
    //     if (!_HasArchetype<Ts...>())
    //     {
    //         _archetypes.emplace_back(CreateArchetype<Ts...>());
    //         return Entity(_GetArchetype<Ts...>().AddEntity(std::forward<Ts>(args)...));
    //     }

    //     return Entity(_GetArchetype<Ts...>().AddEntity(std::forward<Ts>(args)...));
    // }
        
    template <typename ...Ts>
    EntityId CreateEntity(const std::tuple<Ts...>& components)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        if (!_HasArchetype<Ts...>())
        {
            _archetypes.emplace_back(CreateArchetype<Ts...>());
        }
        
        return _GetArchetype<Ts...>().AddEntity(components);
    }

    void RemoveEntity(const Entity& entity);
    void RemoveEntity(const EntityId& entity);
        
    EntitySnapshot GetTemporaryEntitySnapshot(const Entity& entity);
    EntitySnapshot GetTemporaryEntitySnapshot(const EntityId& entity);

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

    // methods for ACTUALLY doing the entity changes
    // void _RemoveEntity(const Entity& entity);
    // void _RemoveEntity(const EntityId& entity);
};
}// namespace Application