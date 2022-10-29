#pragma once

#include <unordered_map>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/type_traits.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application
{
    struct EntityHandler;

    // we should be able to add/remove components and delete entities from here -> needs access to ArchetypeManager! (is this possible?)
    // hard to do because this means we get an ArchetypeManager->EntitySnapshot->ArchetypeManager loop
    struct EntitySnapshot
    {
        EntitySnapshot(const Entity& entity, std::vector<std::unique_ptr<ITemporaryComponentRef>>&& components)
        : _entity(entity)
        {
            std::vector<Core::runtimeId_t> componentTypes;
            componentTypes.reserve(components.size());
            for (const auto& component : components)
            {
                componentTypes.push_back(component->GetComponentType());
            }
            _componentTypes = TypeCollection(std::move(componentTypes));

            _componentReferences = std::move(components);
        }

        // creates an empty snapshot - to be used if the entity no longer exists
        EntitySnapshot(const EntityId& entity)
        : _entity(entity, ArchetypeId())
        {}

        EntitySnapshot() = default;
        EntitySnapshot(EntitySnapshot&&) = default;
        EntitySnapshot& operator=(EntitySnapshot&&) = default;

        EntitySnapshot(const EntitySnapshot& other)
        {
            SCOPED_MEMORY_CATEGORY("ECS");
            _entity = other._entity;
            _componentTypes = other._componentTypes;
            
            for (const auto& component : other._componentReferences)
            {
                _componentReferences.emplace_back(component->CreateCopy());
            }
        }

        EntitySnapshot& operator=(const EntitySnapshot& other)
        {
            SCOPED_MEMORY_CATEGORY("ECS");
            _entity = other._entity;
            _componentTypes = other._componentTypes;

            for (const auto& component : other._componentReferences)
            {
                _componentReferences.emplace_back(component->CreateCopy());
            }
        }

        const EntityId& GetEntityId() const
        {
            return _entity.GetEntityId();
        }

        const TypeCollection& ComponentTypes() const { return _componentTypes; }

        bool ContainsTypes(const TypeCollection& types) const
        {
            const std::vector<Core::runtimeId_t>& typeIds = types.Types();

            for (const Core::runtimeId_t& typeId : typeIds)
            {
                auto typeIter = std::find_if(_componentReferences.begin(), _componentReferences.end(), [typeId](const auto& componentReference)
                {
                    return (componentReference->GetComponentType() == typeId);
                });

                if (typeIter == _componentReferences.end())
                {
                    return false;
                }
            }

            return true;
        }

        template <typename T>
        bool HasComponent() const
        {
            return HasComponent(Core::GetTypeId<T>());
        }

        bool HasComponent(const Core::runtimeId_t& componentId) const
        {
            return (_GetComponentFor(componentId) != nullptr);
        }

        template <typename T>
        T& GetComponent()
        {
            Core::Ptr<void> componentPtr = _GetComponentFor(Core::GetTypeId<T>());
            if (componentPtr == nullptr)
            {
                DEBUG_THROW("EntitySnapshot", "Requested type does not exist");
            }

            return *(static_cast<Core::Ptr<T>>(componentPtr));
        }

        template <typename T>
        const T& GetComponent() const
        {
            Core::Ptr<void> componentPtr = _GetComponentFor(Core::GetTypeId<T>());
            if (componentPtr == nullptr)
            {
                DEBUG_THROW("EntitySnapshot", "Requested type does not exist");
            }

            return *(static_cast<Core::Ptr<T>>(componentPtr));
        }

        std::vector<std::unique_ptr<ITemporaryComponentRef>>& GetComponents()
        {
            return _componentReferences;
        }

        const std::vector<std::unique_ptr<ITemporaryComponentRef>>& GetComponents() const
        {
            return _componentReferences;
        }

        bool IsValid() const
        {
            return _entity.IsValid();
        }

    private:
        friend struct EntityHandler;

        Entity _entity;
        TypeCollection _componentTypes;
        std::vector<std::unique_ptr<ITemporaryComponentRef>> _componentReferences;

        void* _GetComponentFor(const Core::runtimeId_t& type) const
        {
            for (auto&& componentReference : _componentReferences)
            {
                if (componentReference->GetComponentType() == type)
                {
                    return componentReference->GetPtrToComponent();
                }
            }

            return nullptr; // throws due to null should have handled in caller
        }
    };
} // namespace Application