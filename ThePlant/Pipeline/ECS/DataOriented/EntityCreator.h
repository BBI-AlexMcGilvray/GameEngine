#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/Archetype.h"
#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application {
struct EntityCreator;

struct IComponentCreator
{
    virtual Core::runtimeId_t ComponentType() const = 0;
    virtual std::unique_ptr<IComponentList> CreateComponentList() const = 0;
    virtual void CreateComponent(Archetype& archetype, const Entity& entity) const = 0;

    template <typename T>
    const T& ComponentValue()
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

    virtual Core::Ptr<const void> _VoidPtrToComponentValue() const = 0;
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

    void CreateComponent(Archetype& archetype, const Entity& entity) const override
    {
        archetype.GetComponentFor<T>(entity) = _component;
    }

private:
    T _component;

    Core::Ptr<const void> _VoidPtrToComponentValue() const override
    {
        return &_component;
    }
};

struct EntityCreator
{
    // get the representation of the desired archetype
    TypeCollection GetArchetype() const;
    // if the archetype does not exist, this will create one
    Archetype CreateArchetype() const;
    // given the archetype that matches this entity, create the entity within it
    // (ArchetypeManager will use the GetArchetype method - and then potentially the CreateArchetype method - to determine what is passed in here)
    Entity CreateEntity(Archetype& archetype) const;

    template <typename T, typename ...ARGS>
    void AddComponent(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        _componentCreators.emplace_back(std::make_unique<ComponentCreator<T>>(T(std::forward<ARGS>(args)...)));
    }

    template <typename T>
    void RemoveComponent()
    {
        for (auto& iter = _componentCreators.begin(); iter != _componentCreators.end(); ++iter)
        {
            if (iter->GetComponentType() == Core::GetTypeId<T>())
            {
                _componentCreators.erase(iter);
                return;
            }
        }

        throw std::invalid_argument("trying to remove a component that does not exist for the given entity");
    }

private:
    std::vector<std::unique_ptr<IComponentCreator>> _componentCreators;
};
} // namespace Application