#pragma once

#include <exception>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Core/Logging/Logger.h"
#include "Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

template <>
struct std::hash<Core::runtimeId_t>
{
    std::size_t operator()(const Core::runtimeId_t& runtimeId) const
    {
        return static_cast<const uint32_t>(runtimeId);
    }
};

namespace Application {
// this may need to be templated with an inheritance of a base interface so they can be held generically
struct Archetype
{
    template <typename ...Ts>
    friend Archetype CreateArchetype();
    template <typename ...Ts>
    friend Archetype CreateArchetypeFrom_Add(const Archetype& basis);
    template <typename ...Ts>
    friend Archetype CreateArchetypeFrom_Remove(const Archetype& basis);

    Archetype(const Archetype&) = delete;
    Archetype& operator=(const Archetype&) = delete;

    Archetype(Archetype&& other);
    Archetype& operator=(Archetype&& other);

    Entity AddEntity();

    template <typename ...Ts>
    Entity AddEntity(Ts&& ...args)
    {
        Entity newEntity(GetId());

        _AddEntity(newEntity, args...);
        
        return newEntity;
    }

    void TransferEntityTo(Entity& entity, Archetype& destination);

    void RemoveEntity(const Entity& entity);

    template <typename T>
    bool HasComponent() const
    {
        return HasComponent(GetTypeId<T>());
    }

    bool HasComponent(const Core::runtimeId_t& componentId) const;

    const std::vector<EntityId>& GetEntities() const;

    template <typename T>
    T& GetComponentFor(const Entity& entity)
    {
        if (entity.GetArchetypeId() != GetId())
        {
            throw std::invalid_argument("entity does not have valid archetype id");
        }

        // for some reason can't do this in one line or compiler is confused
        IComponentList* componentList = _components.at(GetTypeId<T>()).get();
        return componentList->GetComponentAt<T>(_GetEntityIndex(entity.GetEntityId()));
    }

    template <typename T>
    std::vector<T>& GetComponents()// vector should not be modified, but elements may be
    {
        // for some reason can't do this in one line or compiler is confused
        IComponentList* componentList = _components.at(GetTypeId<T>()).get();
        return componentList->GetComponents<T>();
    }

    template <typename T>
    void SetComponentFor(const Entity& entity, T value)
    {
        GetComponentAt<T>(_GetEntityIndex(entity.GetEntityId())) = value;
    }

    template <typename T, typename ...Ts>
    void SetComponentFor(const Entity& entity, T value, Ts ...args)
    {
        SetComponentFor(entity, std::forward<T>(value));
        SetComponentFor(entity, std::forward<Ts>(args)...);
    }

    bool ContainsTypes(const TypeCollection& types) const;

    bool IsArchetype(const TypeCollection& types) const;

    const ArchetypeId& GetId() const;
    const TypeCollection& GetArchetype() const;

private:
    ArchetypeId _id;
    TypeCollection _types;
    std::vector<EntityId> _entities;
    std::unordered_map<Core::runtimeId_t, std::unique_ptr<IComponentList>> _components;
    
    enum class Constructor { TAG };
    Archetype(Constructor, const Core::IncrementalId& id, const TypeCollection& types, std::vector<std::unique_ptr<IComponentList>>&& components);

    void _AddEntity(const Entity& entity);

    template <typename ...Ts>
    void _AddEntity(const Entity& entity, Ts ...args)
    {
        _entities.emplace_back(entity.GetEntityId());
        _AddComponentForEntity(args...);
    }

    template <typename T>
    void _AddComponentForEntity(const Entity& entity, T value)
    {
        _components.at(GetTypeId<T>())->AddComponent(std::move(value));
    }

    template <typename T, typename ...Ts>
    void _AddComponentForEntity(const Entity& entity, T value, Ts ...args)
    {
        _AddComponentForEntity(entity, std::move(value));
        _AddComponentForEntity(entity, args...);
    }

    size_t _GetEntityIndex(const EntityId& entity)
    {
        for (size_t index = 0; index < _entities.size(); ++index)
        {
            if (_entities[index] == entity)
            {
                return index;
            }
        }

        throw std::invalid_argument("entity does not exist in this archetype");
    }
};

// 'for each' helper should be written for tuples, same as below but takes in a std::function
namespace TUPLE_HELPERS
{
    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    insert(std::tuple<Tp...>& t, std::vector<std::unique_ptr<IComponentList>>& vec)
    { }

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I < sizeof...(Tp), void>::type
    insert(std::tuple<Tp...>& t, std::vector<std::unique_ptr<IComponentList>>& vec)
    {
        vec.emplace_back(std::move(std::get<I>(t)));
        insert<I + 1, Tp...>(t, vec);
    }

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    create_unique_ptrs(std::tuple<Tp...>& t)
    { }

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I < sizeof...(Tp), void>::type
    create_unique_ptrs(std::tuple<Tp...>& t)
    {
        std::get<I>(t) = std::make_unique<decltype(std::get<I>(t))>();
        create_unique_ptrs<I + 1, Tp...>(t);
    }
}

template <typename ...Ts>
std::vector<std::unique_ptr<IComponentList>> CollectIComponentLists()
{
    std::tuple<std::unique_ptr<ComponentList<Ts>>...> instances(std::make_unique<ComponentList<Ts>>()...);
    // TUPLE_HELPERS::create_unique_ptrs(instances);

    std::vector<std::unique_ptr<IComponentList>> collection;
    TUPLE_HELPERS::insert(instances, collection);
    return collection;
}

template <typename ...Ts>
Archetype CreateArchetype()
{
    std::vector<std::unique_ptr<IComponentList>> components = CollectIComponentLists<Ts...>();

    return Archetype(Archetype::Constructor::TAG, GetIncrementalId(), CollectTypes<Ts...>(), std::move(components));
}

template <typename ...Ts>
Archetype CreateArchetypeFrom_Add(const Archetype& basis)
{
    std::vector<std::unique_ptr<IComponentList>> components = CollectIComponentLists<Ts...>();
    for (auto& copyingComponent : basis._components)
    {
        components.emplace_back(copyingComponent.second->CreateEmptyCopy());
    }
    
    return Archetype(Archetype::Constructor::TAG, GetIncrementalId(), AddToCollection<Ts...>(basis.GetArchetype()), std::move(components));
}

template <typename ...Ts>
Archetype CreateArchetypeFrom_Remove(const Archetype& basis)
{
    std::vector<std::unique_ptr<IComponentList>> components;
    for (auto& copyingComponent : basis._components)
    {
        components.emplace_back(std::move(copyingComponent.second->CreateEmptyCopy()));
    }

    TypeCollection typesToRemove = CollectTypes<Ts...>();
    auto typesToRemoveIds = typesToRemove.Types();

    for (auto iter = components.rbegin(); iter = components.rend(); ++iter)
    {
        if (std::find(typesToRemoveIds.begin(), typesToRemoveIds.end(), (*iter)->ComponentType()))
        {
            components.erase(iter.base() - 1); // -1 because reverse iterators are offset
        }
    }

    return Archetype(Archetype::Constructor::TAG, GetIncrementalId(), RemoveFromCollection<Ts...>(basis.GetArchetype()), std::move(components));
}
}// namespace Application
