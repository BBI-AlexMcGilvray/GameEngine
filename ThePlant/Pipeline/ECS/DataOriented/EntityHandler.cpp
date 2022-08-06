#include "Pipeline/ECS/DataOriented/EntityHandler.h"

namespace Application {
    EntityHandler::EntityHandler(const EntityId newEntity)
    : _entity(newEntity)
    {
        _changes |= EntityChange::Created;
    }

    EntityHandler::EntityHandler(const EntitySnapshot& snapshot)
    : _entity(snapshot)
    , _components(snapshot.ComponentTypes())
    {
        // fille _componentCreators with those needed to match the current archetype!
    }

    Archetype EntityHandler::CreateArchetype(Core::Ptr<const Archetype> oldArchetype) const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        TypeCollection finalArchetype = GetFinalArchetype();
        std::vector<std::unique_ptr<IComponentList>> components;

        if (oldArchetype != nullptr)
        {   // need to get the component lists of the right type from the old archetype
            auto oldComponentLists = oldArchetype->_GetComponentListCopies();
            for (auto& oldComponentList : oldComponentLists)
            {
                if (finalArchetype.HasType(oldComponentList->ComponentType()))
                {
                    components.push_back(std::move(oldComponentList));
                }
            }
        }

        // we know the component list types for the new components, handle new ones here
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }

        return Archetype(Archetype::Constructor::TAG, Core::GetInstanceId<ArchetypeId>(), finalArchetype, std::move(components));
    }

    void EntityHandler::CreateNewComponents(Archetype& archetype) const
    {
        for (auto& creater : _componentCreators)
        {
            creater->CreateComponent(archetype, _entity.GetEntityId());
        }
    }
} // namespace Application