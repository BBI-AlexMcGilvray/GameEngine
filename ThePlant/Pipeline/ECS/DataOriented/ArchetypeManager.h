#pragma once

#include <utility>

#include "Pipeline/ECS/DataOriented/Archetype.h"
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
    T& GetComponentFor(const Entity& entity)
    {
        return _GetArchetype(entity.GetArchetypeId()).GetComponentFor<T>(entity);
    }

    // need a way for this to take in a value for the new components
    template <typename ...Ts>
    void AddComponentsTo(Entity& entity)
    {
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = AddToCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Add<Ts...>(oldArchetype));
        }
        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity, newArchetype);
    }

    template <typename ...Ts>
    void AddComponentsTo(Entity& entity, Ts ...args)
    {
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = AddToCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Add<Ts...>(oldArchetype));
        }

        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity, newArchetype);

        newArchetype.SetComponentFor(entity, std::forward<Ts>(args)...);
    }

    template <typename ...Ts>
    void RemoveComponentsFrom(Entity& entity)
    {
        Archetype& oldArchetype = _GetArchetype(entity.GetArchetypeId());
        TypeCollection newArchetypeType = RemoveFromCollection<Ts...>(oldArchetype.GetArchetype());
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(CreateArchetypeFrom_Add<Ts...>(oldArchetype));
        }
        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity, newArchetype);
    }

    // create entity
    template <typename ...Ts>
    Entity CreateEntity()
    {
        if (!_HasArchetype<Ts...>())
        {
            _archetypes.emplace_back(CreateArchetype<Ts...>());
            return Entity(_GetArchetype<Ts...>().AddEntity());
        }

        return Entity(_GetArchetype<Ts...>().AddEntity());
    }

    // must provide an argument for each component type provided
    template <typename ...Ts>
    Entity CreateEntity(Ts ...args)
    {
        if (!_HasArchetype<Ts...>())
        {
            _archetypes.emplace_back(CreateArchetype<Ts...>());
            return Entity(_GetArchetype<Ts...>().AddEntity(std::forward<Ts>(args)...));
        }

        return Entity(_GetArchetype<Ts...>().AddEntity(std::forward<Ts>(args)...));
    }

    void RemoveEntity(const Entity& entity);

    template <typename ...Ts>
    const std::vector<Archetype*> GetArchetypesContaining() const
    {
        TypeCollection types = CollectTypes<Ts...>();

        std::vector<Archetype*> relevantArchetypes;

        for (auto& archetype : _archetypes)
        {
            if (archetype.ContainsTypes(types))
            {
                relevantArchetypes.push_back(&archetype);
            }
        }

        return relevantArchetypes;
    }

private:
    std::vector<Archetype> _archetypes;

    template <typename ...Ts>
    bool _HasArchetype()
    {
        TypeCollection types = CollectTypes<Ts...>();

        return _HasArchetype(types);
    }

    bool _HasArchetype(const TypeCollection& archetypeTypes);

    bool _HasArchetype(const ArchetypeId& archetypeId);

    template <typename ...Ts>
    Archetype& _GetArchetype()
    {
        TypeCollection types = CollectTypes<Ts...>();

        return _GetArchetype(types);
    }

    Archetype& _GetArchetype(const TypeCollection& archetypeTypes);

    Archetype& _GetArchetype(const ArchetypeId& archetypeId);
};
}// namespace Application