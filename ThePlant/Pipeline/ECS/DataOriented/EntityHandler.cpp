#include "Pipeline/ECS/DataOriented/EntityHandler.h"

namespace Application {
    EntityHandler::EntityHandler()
    {
        _changes |= EntityChange::Created;
    }

    EntityHandler::EntityHandler(const EntitySnapshot& snapshot)
    : _entity(std::move(snapshot._entity))
    , _components(snapshot.ComponentTypes())
    {
        // fille _componentCreators with those needed to match the current archetype!
    }

    const TypeCollection& EntityHandler::GetFinalArchetype() const { return _components; }

    Archetype EntityHandler::CreateArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<std::unique_ptr<IComponentList>> components;
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }
        DEBUG_THROW("EntityHandler", "This component list is not create, we need to get the applicable ones from the initial archetype as well");

        return Archetype(Archetype::Constructor::TAG, Core::GetInstanceId<ArchetypeId>(), GetFinalArchetype(), std::move(components));
    }

    void EntityHandler::CreateEntity(Archetype& archetype, const EntityId& entity) const
    {
        VERIFY(_changes.HasAllFlags(EntityChange::Created), "if this is called, it must be a new entity");
        for (auto& creater : _componentCreators)
        {
            creater->CreateComponent(archetype, entity);
        }
    }

    void EntityHandler::CreateNewComponents(Archetype& archetype) const
    {
        VERIFY(!(_changes.HasAllFlags(EntityChange::Created)), "this should not be called for new entities");
        for (auto& creater : _componentCreators)
        {
            creater->CreateComponent(archetype, _entity.GetEntityId());
        }
    }

    BitmaskEnum<EntityChange> EntityHandler::GetChanges() const
    {
        return _changes;
    }

    void EntityHandler::DeleteEntity()
    {
        _changes |= EntityChange::Deleted;
    }
} // namespace Application