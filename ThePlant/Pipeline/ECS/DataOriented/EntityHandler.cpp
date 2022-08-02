#include "Pipeline/ECS/DataOriented/EntityHandler.h"

namespace Application {
    EntityHandler::EntityHandler(const EntityId newEntity)
    : _entity(newEntity, ArchetypeId())
    {
        _changes |= EntityChange::Created;
    }

    EntityHandler::EntityHandler(const EntitySnapshot& snapshot)
    : _entity(std::move(snapshot._entity))
    , _components(snapshot.ComponentTypes())
    {
        // fille _componentCreators with those needed to match the current archetype!
    }

    Archetype EntityHandler::CreateArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<std::unique_ptr<IComponentList>> components;
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }
        DEBUG_THROW("EntityHandler", "This component list is not complete, we need to get the applicable ones from the initial archetype as well");

        return Archetype(Archetype::Constructor::TAG, Core::GetInstanceId<ArchetypeId>(), GetFinalArchetype(), std::move(components));
    }

    void EntityHandler::CreateNewComponents(Archetype& archetype) const
    {
        for (auto& creater : _componentCreators)
        {
            creater->CreateComponent(archetype, _entity.GetEntityId());
        }
    }
} // namespace Application