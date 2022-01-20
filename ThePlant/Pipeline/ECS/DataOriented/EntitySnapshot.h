#pragma once

#include <unordered_map>

#include "Core/Headers/type_traits.h"
#include "Core/Logging/Logger.h"

#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application
{
    struct EntitySnapshot
    {
        EntitySnapshot(const EntityId& entity, std::vector<std::unique_ptr<ITemporaryComponentRef>>&& components)
        : _entity(entity)
        {
            _componentReferences = std::move(components);
        }

        EntitySnapshot() = default;
        EntitySnapshot(EntitySnapshot&&) = default;
        EntitySnapshot& operator=(EntitySnapshot&&) = default;

        EntitySnapshot(const EntitySnapshot& other)
        {
            for (const auto& component : other._componentReferences)
            {
                _componentReferences.emplace_back(component->CreateCopy());
            }
        }
        EntitySnapshot& operator=(const EntitySnapshot& other)
        {
            for (const auto& component : other._componentReferences)
            {
                _componentReferences.emplace_back(component->CreateCopy());
            }
        }

        EntityId GetEntity() const
        {
            return _entity;
        }

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

        bool HasComponent(const Core::runtimeId_t& componentId) const;

        template <typename T>
        T& GetComponent()
        {
            Core::Ptr<void> componentPtr = _GetComponentFor(Core::GetTypeId<T>());
            if (componentPtr == nullptr)
            {
                DEBUG_THROW("EntitySnapshot", "Requested type does not exist");
            }

            return *(static_cast<Core::Ptr<T>(componentPtr));
        }

        bool IsValid() const
        {
            return _entity.IsValid();
        }

    private:
        EntityId _entity;
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

            DEBUG_THROW("EntitySnapshot", "Requested type does not exist");
        }
    };
} // namespace Application