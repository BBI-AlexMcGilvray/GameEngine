#include "Pipeline/ECS/DataOriented/EntityCreator.h"

#include "Core/IdTypes/IncrementalId.h"

namespace Application {
    TypeCollection EntityCreator::GetArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<Core::runtimeId_t> types;
        for (auto& componentCreator : _componentCreators)
        {
            types.emplace_back(componentCreator->ComponentType());
        }

        return TypeCollection(std::move(types));
    }

    Archetype EntityCreator::CreateArchetype() const
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        std::vector<std::unique_ptr<IComponentList>> components;
        for (auto& componentCreator : _componentCreators)
        {
            components.emplace_back(componentCreator->CreateComponentList());
        }

        return Archetype(Archetype::Constructor::TAG, Core::GetIncrementalId(), GetArchetype(), std::move(components));
    }

    Entity EntityCreator::CreateEntity(Archetype& archetype) const
    {
        Entity entity = archetype.AddEntity();

        for (auto& componentCreator : _componentCreators)
        {
            componentCreator->CreateComponent(archetype, entity);
        }

        return entity;
    }
} // namespace Application