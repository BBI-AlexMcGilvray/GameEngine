#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Materials/Core/Debugging/Headers/Macros.h"
#include "Materials/Core/IdTypes/RuntimeId.h"
#include "Materials/Core/Logging/LogFunctions.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
template <typename T>
struct ComponentList;

// NOTE: NOT to be used as a permanent-reference, they reference is liable to break at any point
struct ITemporaryComponentRef
{
    ITemporaryComponentRef() = default;
    ITemporaryComponentRef(const ITemporaryComponentRef&) = default;
    ITemporaryComponentRef(ITemporaryComponentRef&&) = default;
    ITemporaryComponentRef& operator=(ITemporaryComponentRef&&) = default;
    ITemporaryComponentRef& operator=(const ITemporaryComponentRef&) = default;

    virtual Core::runtimeId_t GetComponentType() const = 0;
    virtual std::unique_ptr<ITemporaryComponentRef> CreateCopy() const = 0;

    // If you are calling this, the type check is up to you
    Core::Ptr<void> GetPtrToComponent() const
    {
        return _GetPtrToComponent();
    }

    template <typename T>
    T& GetComponent()
    {
        if (Core::GetTypeId<T>() == GetComponentType())
        {
            DEBUG_THROW("ITemporaryComponentRef", "Requested type does not exist");
        }
        
        return *static_cast<Core::Ptr<T>>(_GetPtrToComponent());
    }

private:
    virtual Core::Ptr<void> _GetPtrToComponent() const = 0;
};

// NOTE: NOT to be used as a permanent-reference, they reference is liable to break at any point
template <typename T>
struct TemporaryComponentRef : public ITemporaryComponentRef
{
    TemporaryComponentRef(T& component)
    : _component(component)
    {}

    TemporaryComponentRef() = default;
    TemporaryComponentRef(const TemporaryComponentRef&) = default;
    TemporaryComponentRef(TemporaryComponentRef&&) = default;
    TemporaryComponentRef& operator=(const TemporaryComponentRef&) = default;
    TemporaryComponentRef& operator=(TemporaryComponentRef&&) = default;

    Core::runtimeId_t GetComponentType() const override { return Core::GetTypeId<T>(); }
    std::unique_ptr<ITemporaryComponentRef> CreateCopy() const override
    {
        return std::make_unique<TemporaryComponentRef<T>>(_component);
    }

private:
    T& _component;

    Core::Ptr<void> _GetPtrToComponent() const override { return &_component; }
};

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
            DEBUG_THROW("IComponentList", "type does not match that held by the component list");
        }

        static_cast<ComponentList<T>&>(*this).AddComponent(std::move(value));
    }

    template <typename T>
    T& GetComponentAt(const size_t& index)
    {
        // should be in debug only
        if (!_IsCorrectType<T>())
        {
            DEBUG_THROW("IComponentList", "type does not match that held by the component list");
        }

        return *(static_cast<T*>(_VoidPtrToComponentAt(index)));
    }

    template <typename T>
    std::vector<T>& GetComponents() // vector should not be modified, but elements may be
    {
        // should be in debug only
        if (!_IsCorrectType<T>())
        {
            DEBUG_THROW("IComponentList", "type does not match that held by the component list");
        }

        return *(static_cast<std::vector<T>*>(_VoidPtrToComponentsVector()));
    }

    virtual std::unique_ptr<ITemporaryComponentRef> GetTemporaryComponentRef(const size_t& index) = 0;

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
        DEBUG_ASSERT(index < _components.size());

        _components.erase(_components.begin() + index);
    }

    std::unique_ptr<ITemporaryComponentRef> GetTemporaryComponentRef(const size_t& index) override
    {
        return std::make_unique<TemporaryComponentRef<T>>(_ComponentAt(index));
    }

private:
    // _entities and _components must be kept in sync (i.e. _entities[X] corresponds to _components[X])
    std::vector<T> _components;

    void* _VoidPtrToComponentAt(const size_t& index) override
    {
        return &_ComponentAt(index);
    }

    void* _VoidPtrToComponentsVector() override
    {
        return &_components;
    }

    T& _ComponentAt(const size_t& index)
    {
        DEBUG_ASSERT(index < _components.size());

        return _components[index];
    }
};
}// namespace Application
