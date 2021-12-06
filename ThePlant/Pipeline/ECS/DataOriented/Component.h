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
    virtual void AddComponent() = 0;
    virtual void RemoveComponentAt(const size_t& index) = 0;
    virtual void MoveEntityTo(const size_t& index, IComponentList& destination) = 0;

    template <typename T>
    void AddComponent(T value)
    {
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        static_cast<ComponentList<T>&>(*this).AddComponent(std::move(value));
    }

    template <typename T>
    T& GetComponentAt(const size_t& index)
    {
        // should be in debug only
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        return *(static_cast<T*>(_VoidPtrToComponentAt(index)));
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
    virtual void* _VoidPtrToComponentAt(const size_t& index) = 0;
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

    void AddComponent() override
    {
        AddComponent(T());
    }

    void AddComponent(T value)
    {
        _components.emplace_back(std::move(value));
    }

    void MoveEntityTo(const size_t& index, IComponentList& destination) override
    {
        // should be debug only
        if (!_IsCorrectType(destination.ComponentType()))
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        ComponentList<T>& trueDestination = static_cast<ComponentList<T>&>(destination);
        trueDestination._ComponentAt(index) = std::move(_ComponentAt(index));
        RemoveComponentAt(index);
    }

    void RemoveComponentAt(const size_t& index) override
    {
        VERIFY(index < _components.size());

        _components.erase(_components.begin() + index);
    }

private:
    // _entities and _components must be kept in sync (i.e. _entities[X] corresponds to _components[X])
    std::vector<T> _components;

    void* _VoidPtrToComponentAt(const size_t& index) override
    {c
        return &_ComponentAt(index);
    }

    void* _VoidPtrToComponentsVector() override
    {
        return &_components;
    }

    T& _ComponentAt(const size_t& index)
    {
        VERIFY(index < _components.size());

        return _components[index];
    }
};
}// namespace Application
