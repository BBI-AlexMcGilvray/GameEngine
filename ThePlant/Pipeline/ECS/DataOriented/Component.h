#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Materials/Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
// template <typename T>
// struct ComponentWrapper // may not want to use this, could intead have 2 lists (entityid and component) that would just need to be kept in sync
// {
//     template <typename C>
//     friend MakeComponentFor(const EntityId& entity);

//     ComponentWrapper() = delete;
//     // only one component wrapper should exist for each entity
//     ComponentWrapper(const ComponentWrapper&) = delete;
//     ComponentWrapper& operator=(const ComponentWrapper&) = delete;

//     ComponentWrapper(ComponentWrapper&& other)
//     {
//         _entity = std::move(other._entity);
//         _component = std::move(other._component);
//     }

//     ComponentWrapper& operator=(ComponentWrapper&& other)
//     {
//         _entity = std::move(other._entity);
//         _component = std::move(other._component);
//     }

//     bool BelongsTo(const EntityId& entity) const { return _entity == entity; }

//     void TakeDataFrom(const ComponentWrapper<T>& source)
//     {
//         _component = std::move(source._component);
//     }

//     constexpr operator T() { return _component; }
    
// private:
//     EntityId _entity; // we are indexing component->entity instead of entity->component
//     T _component;

//     ComponentWrapper(const EntityId& entity, T component)
//     : _entity(entity)
//     , _component(component)
//     {}
// };

// // may want to find a way to make this take in constructor parameters
// template <typename T>
// ComponentWrapper<T> MakeComponentFor(const EntityId& entity)
// {
//     // in debug mode this should iterate over a debug list of all entities to ensure we never do this for a given entity more than once! (per component type) unless that component has been destroyed
//     // would make use of the ArchetypeManager to check for such a thing i imagine
//     return ComponentWrapper<T>(entity, T());
// }

template <typename T>
struct ComponentList;

struct IComponentList
{
    virtual Core::runtimeId_t ComponentType() const = 0;
    virtual std::unique_ptr<IComponentList> CreateEmptyCopy() const = 0;
    virtual void AddComponentFor(const EntityId& entity) = 0;
    virtual void RemoveComponentFor(const EntityId& entity) = 0;
    virtual void MoveEntityTo(const EntityId& entity, IComponentList& destination) = 0;

    template <typename T>
    void AddComponentFor(const EntityId& entity, T value)
    {
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        static_cast<ComponentList<T>&>(*this).AddComponentFor(entity, std::move(value));
    }

    template <typename T>
    T& GetComponentFor(const EntityId& entity)
    {
        // should be in debug only
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        return *(static_cast<T*>(_VoidPtrToComponentFor(entity)));
    }

    template <typename T>
    std::vector<T>& GetComponents() // vector should not be modified, but elements may be
    {
        // should be in debug only
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        return *(static_cast<std::vector<T>*>(_VoidPtrToComponentsVector()));
    }

protected:
    template <typename T>
    bool _IsCorrectType() const { return _IsCorrectType(GetTypeId<T>()); } // could be compiled out when not in debug

    bool _IsCorrectType(const Core::runtimeId_t& type) const { return (type == ComponentType()); }

private:
    virtual void* _VoidPtrToComponentFor(const EntityId& entity) = 0;
    virtual void* _VoidPtrToComponentsVector() = 0;
};

template <typename T>
struct ComponentList : public IComponentList
{
    Core::runtimeId_t ComponentType() const override { return Core::GetTypeId<T>(); }

    std::unique_ptr<IComponentList> CreateEmptyCopy() const override 
    {
        return std::make_unique<ComponentList<T>>();
    }

    void AddComponentFor(const EntityId& entity) override
    {
        AddComponentFor(entity, T());
    }

    void AddComponentFor(const EntityId& entity, T value)
    {
        _entities.emplace_back(entity);
        _components.emplace_back(std::move(value));
    }

    void MoveEntityTo(const EntityId& entity, IComponentList& destination) override
    {
        // should be debug only
        if (!_IsCorrectType(destination.ComponentType()))
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        ComponentList<T>& trueDestination = static_cast<ComponentList<T>&>(destination);
        trueDestination._ComponentFor(entity) = std::move(_ComponentFor(entity));
        RemoveComponentFor(entity);
    }

    void RemoveComponentFor(const EntityId& entity) override
    {
        std::size_t index = 0;
        for (auto& _entity : _entities)
        {
            if (_entity == entity)
            {
                _entities.erase(_entities.begin() + index);
                _components.erase(_components.begin() + index);
                return;
            }

            ++index;
        }

        throw std::invalid_argument("entity is not held by this component list");
    }

private:
    // _entities and _components must be kept in sync (i.e. _entities[X] corresponds to _components[X])
    std::vector<EntityId> _entities;
    std::vector<T> _components;

    void* _VoidPtrToComponentFor(const EntityId& entity) override
    {
        return &_ComponentFor(entity);
    }

    void* _VoidPtrToComponentsVector() override
    {
        return &_components;
    }

    T& _ComponentFor(const EntityId& entity)
    {
        std::size_t index = 0;
        for (auto& _entity : _entities)
        {
            if (_entity == entity)
            {
                return _components[index];
            }

            ++index;
        }

        throw std::invalid_argument("entity is not held by this component list");
    }
};
}// namespace Application
