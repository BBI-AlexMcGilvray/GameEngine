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
#include "Pipeline/ECS/DataOriented/EntityCreator.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application {
enum class EntityChange
{
    AddComponent,
    RemoveComponent,
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
    EntityChanger(EntitySnapshot&& snapshot);

    // get the representation of the desired archetype
    TypeCollection GetFinalArchetype() const;
    // if the archetype does not exist, this will create one
    Archetype CreateFinalArchetype() const;
    // given the archetype that matches this entity, create the entity within it
    // (ArchetypeManager will use the GetArchetype method - and then potentially the CreateArchetype method - to determine what is passed in here)
    Entity ApplyChanges(Archetype& archetype) const;

    BitmaskEnum<EntityChange> GetChanges() const;

    void DeleteEntity();

    template <typename T, typename ...ARGS>
    EntityCreator& AddComponent(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        _componentCreators.emplace_back(std::make_unique<ComponentCreator<T>>(T(std::forward<ARGS>(args)...)));

        _changes |= EntityChange::AddComponent;
        return *this; // to allow 'chaining'
    }

    template <typename T>
    EntityCreator& RemoveComponent()
    {
        for (auto& iter = _componentCreators.begin(); iter != _componentCreators.end(); ++iter)
        {
            if (iter->GetComponentType() == Core::GetTypeId<T>())
            {
                _componentCreators.erase(iter);

                _changes |= EntityChange::RemoveComponent;
                return *this;
            }
        }

        throw std::invalid_argument("trying to remove a component that does not exist for the given entity");
    }

private:
// should definitely be possible for this to be an entity (maybe even entity snapshots can have entity, since we wont change archetypes until the end)
    Entity _entity; // this means _nothing_ except snapshots and this should be using Entity, everything else should use EntityId
    BitmaskEnum<EntityChange> _changes;
    std::vector<std::unique_ptr<IComponentCreator>> _componentCreators;
};
} // namespace Application