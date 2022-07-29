#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/Headers/BitmaskEnum.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/Archetype.h"
#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/ComponentCreator.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application {
enum class EntityChange
{
    ComponentAdded,
    ComponentRemoved,
    Delete
};

// ArchetypeManager (ECS forwards) will, whenever a chage is made to an entity (removal, component add/remove) will
//      - check if it has a changer
//          - if not, make one
//      - add change request to changer (even if it has been set for deletion? maybe in debug so we can track...)
// There will be another method that is 'apply changes' that will go through all changes and apply
// This means we should move entities less often (-> performance gains) and all changes are made NEXT frame (less worrying about weird knock-ons of ordering)
struct EntityChanger
{
    EntityChanger(const EntitySnapshot& snapshot);

    const EntityId& GetEntity() const { return _entity.GetEntityId(); }
    const ArchetypeId& GetArchetype() const { return _entity.GetArchetypeId(); }

    // get the representation of the desired archetype
    const TypeCollection& GetFinalArchetype() const;
    Archetype CreateArchetype() const;
    void CreateNewComponents(Archetype& archetype) const;

    BitmaskEnum<EntityChange> GetChanges() const;

    // no way to save an entity from being deleted, that should be handled by the systems/components
    void DeleteEntity();

    template <typename T, typename ...ARGS>
    EntityChanger& AddComponent(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        if (_components.Has(Core::GetTypeId<T>()))
        {
            DEBUG_THROW("EntityChanger", "Adding component that already exists!");
        }

        _components = AddToCollection<T>(_components);
        _componentCreators.emplace_back(std::make_unique<ComponentCreator<T>>(T(std::forward<ARGS>(args)...)));
        _changes |= EntityChange::ComponentAdded;
        return *this; // to allow 'chaining'
    }

    template <typename T>
    EntityChanger& RemoveComponent()
    {
        if (!_components.HasType(Core::GetTypeId<T>()))
        {
            DEBUG_THROW("EntityChanger", "Removing component that doesn't exist");
        }

        _components = RemoveFromCollection<T>(_components);
        if (auto iter = std::find(_componentCreators.begin(), _componentCreators.end(), [](const auto& creator)
        {
            return creator->ComponentType() == Core::GetTypeId<T>();
        }; iter != _componentCreators.end()))
        {
            _componentCreators.erase(iter);
        }
        _changes |= EntityChange::ComponentRemoved;
    }

private:
    Entity _entity; // this means _nothing_ except snapshots and this should be using Entity, everything else should use EntityId
    BitmaskEnum<EntityChange> _changes;
    TypeCollection _components;
    std::vector<std::unique_ptr<IComponentCreator>> _componentCreators;
    // NOTE: we need to replace the ArchetypeManager::Add/RemoveComponent calls to redirect to create/update an instance of this class
};
} // namespace Application