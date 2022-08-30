#pragma once

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"

namespace Application
{
// when will this run? just at the end of all systems/right before the updates are applied?
// is there any way to only run this when an entity is destroyed to limit the frequency?
struct ParentSyncSystem : public System<ParentSyncSystem>
{
    ParentSyncSystem(ECS& ecs)
    : System<ParentSyncSystem>()
    , _ecs(ecs)
    {}

    // because we do updates before ECS is run, deleted parents are guaranteed to have been destroyed
    // so, that should limit where/when we do this...
    // problem example: parent is destroyed -> we should no longer have parent component -> we don't remove until the end -> will dependent systems handle the parent missing?
    // maybe this is a case where 'immediate change application' is needed?
    void Execute(ArchetypeManager& archetypeManager) const override
    {
        const std::unordered_map<EntityId, EntityHandler>& pendingChanges = archetypeManager.GetPendingChanges();
        if (!RelevantPendingChanges(pendingChanges))
        {
            return;
        }

        std::vector<Core::Ptr<Archetype>> archetypes = archetypeManager.GetArchetypesContaining<ParentComponent>();

        // vector of all entities and their parents
        std::vector<SyncStruct> childParentMapping;
        // calculate size ahead of time for efficiency
        size_t size = 0;
        for (auto& archetype : archetypes)
        {
            size += archetype->GetEntities().size();
        }
        childParentMapping.reserve(size);

        // populate the mapping
        for (auto& archetype : archetypes)
        {
            const auto& entities = archetype->GetEntities();
            auto& parents = archetype->GetComponents<ParentComponent>();
            VERIFY(entities.size() == parents.size(), "These must always match");
            
            for (size_t index = 0; index < entities.size(); ++index)
            {
                childParentMapping.push_back({ entities[index], &parents[index] });
            }
        }

        // sort the mapping (we need to delete possible parents before checking their children)
        std::sort(childParentMapping.begin(), childParentMapping.end(), [](const auto& child1, const auto& child2)
        {
            // if child1 depends on child2, child1 must come after
            if (child1.parentComponent->entity == child2.child)
            {
                return false;
            }
            // if child2 depends on child1, child1 must come first
            if (child2.parentComponent->entity == child1.child)
            {
                return true;
            }

            // if we don't have a definitive mapping, return assume child1 must come after to enforce checking against the rest of the elements
            return false;
        });

        // process
        for (auto& childParent : childParentMapping)
        {
            auto parentIter = pendingChanges.find(childParent.parentComponent->entity);
            if (parentIter == pendingChanges.end())
            {
                continue;
            }

            if (parentIter->second.GetChanges().HasAllFlags(EntityChange::Deleted))
            {
                UpdateEntity(archetypeManager, childParent);
            }
        }
    }

private:
    struct SyncStruct
    {
        EntityId child;
        Core::Ptr<ParentComponent> parentComponent;
    };
    ECS& _ecs;

    static bool RelevantPendingChanges(const std::unordered_map<EntityId, EntityHandler>& pendingChanges)
    {
        for (const auto& pendingChange : pendingChanges)
        {
            if (pendingChange.second.GetChanges().HasAllFlags(EntityChange::Deleted))
            {
                return true;
            }
        }

        return false;
    }

    static void UpdateEntity(ArchetypeManager& archetypeManager, SyncStruct& syncStruct)
    {
        switch (syncStruct.parentComponent->behaviour)
        {
            case ParentComponent::LossBehaviour::Destroy:
            {
                archetypeManager.RemoveEntity(syncStruct.child);
                break;
            }
            case ParentComponent::LossBehaviour::Inherit:
            {
                if (archetypeManager.HasComponent<ParentComponent>(syncStruct.parentComponent->entity))
                {
                    syncStruct.parentComponent->entity = archetypeManager.GetComponentFor<ParentComponent>(syncStruct.parentComponent->entity).entity;
                    break;
                }
                else
                {   // parent doesn't have parent component -> inherit lack of parent component
                    archetypeManager.RemoveComponent<ParentComponent>(syncStruct.child);
                    break;
                }
            }
            case ParentComponent::LossBehaviour::Release:
            {
                archetypeManager.RemoveComponent<ParentComponent>(syncStruct.child);
                break;
            }
        }
    }
};
} // namespace Application