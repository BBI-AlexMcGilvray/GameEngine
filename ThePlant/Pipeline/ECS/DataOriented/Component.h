#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/IdTypes/RuntimeId.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TemporaryComponentRef.h"

namespace Application {
struct IComponentList
{
    virtual Core::runtimeId_t ComponentType() const = 0;
    virtual std::unique_ptr<IComponentList> CreateEmptyCopy() const = 0;
    virtual void AddComponent() = 0;
    virtual void RemoveComponentAt(const size_t& index) = 0;
    virtual void MoveEntityTo(const size_t& index, IComponentList& destination, const size_t& destinationIndex) = 0;

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
    bool _IsCorrectType() const { return _IsCorrectType(Core::GetTypeId<T>()); } // could be compiled out when not in debug

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
        SCOPED_MEMORY_CATEGORY("ECS");
        return std::make_unique<ComponentList<T>>();
    }

    void AddComponent() override
    {
        AddComponent(T());
    }

    void AddComponent(T value)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        _components.emplace_back(std::move(value));
    }

    void MoveEntityTo(const size_t& index, IComponentList& destination, const size_t& destinationIndex) override
    {
        // should be debug only
        if (!_IsCorrectType(destination.ComponentType()))
        {
            throw std::invalid_argument("type does not match that held by the component list");
        }

        ComponentList<T>& trueDestination = static_cast<ComponentList<T>&>(destination);
        trueDestination._ComponentAt(destinationIndex) = std::move(_ComponentAt(index));
        RemoveComponentAt(index);
    }

    void RemoveComponentAt(const size_t& index) override
    {
        DEBUG_ASSERT(index < _components.size());

        _components.erase(_components.begin() + index);
    }

    std::unique_ptr<ITemporaryComponentRef> GetTemporaryComponentRef(const size_t& index) override
    {
        SCOPED_MEMORY_CATEGORY("ECS");
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
