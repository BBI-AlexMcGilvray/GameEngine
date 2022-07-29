#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/IdTypes/RuntimeId.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
struct IComponentCreator;

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

    virtual std::unique_ptr<IComponentCreator> GetComponentCreator() const = 0;

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
        SCOPED_MEMORY_CATEGORY("ECS");
        return std::make_unique<TemporaryComponentRef<T>>(_component);
    }

    virtual std::unique_ptr<IComponentCreator> GetComponentCreator() const override
    {
        return std::make_unique<ComponentCreator<T>>();
    }

private:
    T& _component;

    Core::Ptr<void> _GetPtrToComponent() const override { return &_component; }
};
}// namespace Application
