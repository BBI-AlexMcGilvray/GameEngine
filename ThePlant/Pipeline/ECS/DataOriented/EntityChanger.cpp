#include "Pipeline/ECS/DataOriented/EntityChanger.h"

namespace Application {
    EntityChanger::EntityChanger(EntitySnapshot&& snapshot)
    : _entity(std::move(snapshot.GetEntity()))
    {
        // iterate over snapshot's types and add them all here as compoentCreators
    }

    TypeCollection EntityChanger::GetFinalArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<Core::runtimeId_t> types;
        for (auto& componentCreator : _componentCreators)
        {
            types.emplace_back(componentCreator->ComponentType());
        }

        return TypeCollection(std::move(types));
    }

    Archetype EntityChanger::CreateFinalArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<std::unique_ptr<IComponentList>> components;
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }

        return Archetype(Archetype::Constructor::TAG, Core::GetIncrementalId(), GetFinalArchetype(), std::move(components));
    }

    Entity EntityChanger::ApplyChanges(Archetype& archetype) const
    {
        Entity entity = archetype.AddEntity();

        for (auto& componentCreator : _componentCreators)
        {
            componentCreator->CreateComponent(archetype, entity);
        }

        return entity;
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