#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/Archetype.h"
#include "Pipeline/ECS/DataOriented/Component.h"

namespace Application {

struct IComponentCreator
{
    virtual Core::runtimeId_t ComponentType() const = 0;
    virtual std::unique_ptr<IComponentList> CreateComponentList() const = 0;
    virtual void CreateComponent(Archetype& archetype, const EntityId& entity) const = 0;

    template <typename T>
    T& ComponentValue()
    {
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component creator");
        }

        return *(static_cast<T*>(_VoidPtrToComponentValue()));
    }
    
    template <typename T>
    const T& ComponentValue() const
    {
        if (!_IsCorrectType<T>())
        {
            throw std::invalid_argument("type does not match that held by the component creator");
        }

        return *(static_cast<const T*>(_VoidPtrToComponentValue()));
    }

private:
    template <typename T>
    bool _IsCorrectType() const { return _IsCorrectType(GetTypeId<T>()); } // could be compiled out when not in debug

    bool _IsCorrectType(const Core::runtimeId_t& type) const { return (type == ComponentType()); }

    virtual Core::Ptr<void> _VoidPtrToComponentValue() = 0;
};

template <typename T>
struct ComponentCreator : public IComponentCreator
{
    ComponentCreator(const T& component)
    : _component(component)
    {}

    ComponentCreator() = default;
    ComponentCreator(const ComponentCreator&) = default;
    ComponentCreator(ComponentCreator&&) = default;
    ComponentCreator& operator=(const ComponentCreator&) = default;
    ComponentCreator& operator=(ComponentCreator&&) = default;

    Core::runtimeId_t ComponentType() const override { return Core::GetTypeId<T>(); }

    std::unique_ptr<IComponentList> CreateComponentList() const override
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        return std::make_unique<ComponentList<T>>();
    }

    void CreateComponent(Archetype& archetype, const EntityId& entity) const override
    {
        archetype.GetComponentFor<T>(entity) = _component;
    }

private:
    T _component;

    Core::Ptr<void> _VoidPtrToComponentValue() override
    {
        return &_component;
    }
};
} // namespace Application