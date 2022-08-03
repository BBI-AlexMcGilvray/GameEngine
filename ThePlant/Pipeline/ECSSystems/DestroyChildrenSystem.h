#pragma once

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"

namespace Application
{
// when will this run? just at the end of all systems/right before the updates are applied?
// is there any way to only run this when an entity is destroyed to limit the frequency?
struct DestroyChildrenSystem : public System<DestroyChildrenSystem>
{
    DestroyChildrenSystem(ECS& ecs)
    : System<DestroyChildrenSystem>("DestroyChildrenSystem")
    , _ecs(ecs)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> archetypes = archetypeManager.GetArchetypesContaining<ParentComponent>();

        for (auto& archetype : archetypes)
        {
            ApplyToArchetype(_ecs, archetype->GetEntities(), archetype->GetComponents<ParentComponent>());
        }
    }

private:
    ECS& _ecs;

    static void ApplyToArchetype(ECS& ecs, const std::vector<EntityId>& entities, std::vector<ParentComponent>& components)
    {
        VERIFY(entities.seize() == components.size());

        for (size_t index = 0; index < entities.size(); ++index)
        {
            if (!ecs.EntityExists(components[index].entity))
            {
                UpdateEntity(ecs, entities[index], components[index);
            }
        }
    }

    static void UpdateEntity(ECS& ecs, EntityId entity, ParentComponent& component)
    {
        switch (component.behaviour)
        {
            case ParentComponent::LossBehaviour::Destroy:
            {
                ecs.RemoveEntity(entity);
                break;
            }
            case ParentComponent::LossBehaviour::Inherit:
            {
                if (ecs.HasComponent<ParentComponent>(component.entity))
                {
                    component.entity = ecs.GetComponentFor<ParentComponent>(component.entity).entity;
                    break;
                }
                // fall-through to release otherwise (inherit the lack of parent)
            }
            case ParentComponent::LossBehaviour::Release:
            {
                ecs.RemoveComponent<ParentComponent>(entity);
                break;
            }
        }
    }
}
} // namespace Application