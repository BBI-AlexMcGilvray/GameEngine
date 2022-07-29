#include "Pipeline/ECS/DataOriented/EntityChanger.h"

namespace Application {
    EntityChanger::EntityChanger(const EntitySnapshot& snapshot)
    : _entity(std::move(snapshot._entity))
    , _components(snapshot.ComponentTypes())
    {
        // _componentCreators = snapshot.GetComponentCreators();
    }

    const TypeCollection& EntityChanger::GetFinalArchetype() const { return _components; }

    Archetype EntityChanger::CreateArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<std::unique_ptr<IComponentList>> components;
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }

        return Archetype(Archetype::Constructor::TAG, Core::GetInstanceId<ArchetypeId>(), GetFinalArchetype(), std::move(components));
    }

    void EntityChanger::CreateNewComponents(Archetype& archetype) const
    {
        for (auto& creater : _componentCreators)
        {
            creater->CreateComponent(archetype, _entity.GetEntityId());
        }
    }

    BitmaskEnum<EntityChange> EntityChanger::GetChanges() const
    {
        return _changes;
    }

    void EntityChanger::DeleteEntity()
    {
        _changes |= EntityChange::Delete;
    }
} // namespace Application