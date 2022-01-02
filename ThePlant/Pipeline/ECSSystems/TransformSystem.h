#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"

namespace Application {
struct LocalTransformResetSystem : public System<LocalTransformResetSystem, LocalTransformComponent>
{
    static void ApplyToArchetype(std::vector<LocalTransformComponent>& localTransforms)
    {
        for (auto& localTransform : localTransforms)
        {
            localTransform.transform.Reset();
        }
    }   
};

struct LocalTransformPositionSystem : public System<LocalTransformPositionSystem, LocalTransformComponent, PositionComponent>
{
    static void ApplyToArchetype(std::vector<LocalTransformComponent>& localTransforms, std::vector<PositionComponent>& positions)
    {
        VERIFY(localTransforms.size() == positions.size());
        for (size_t index = 0; index < localTransforms.size(); ++index)
        {
            localTransforms[index].transform.SetPosition(positions[index].position);
        }
    }   
};

struct LocalTransformScaleSystem : public System<LocalTransformScaleSystem, LocalTransformComponent, ScaleComponent>
{
    static void ApplyToArchetype(std::vector<LocalTransformComponent>& localTransforms, std::vector<ScaleComponent>& scales)
    {
        VERIFY(localTransforms.size() == scales.size());
        for (size_t index = 0; index < localTransforms.size(); ++index)
        {
            localTransforms[index].transform.SetScale(scales[index].scale);
        }
    }   
};

struct LocalTransformRotationSystem : public System<LocalTransformRotationSystem, LocalTransformComponent, RotationComponent>
{
    static void ApplyToArchetype(std::vector<LocalTransformComponent>& localTransforms, std::vector<RotationComponent>& rotations)
    {
        VERIFY(localTransforms.size() == rotations.size());
        for (size_t index = 0; index < localTransforms.size(); ++index)
        {
            localTransforms[index].transform.SetRotation(rotations[index].rotation);
        }
    }   
};

struct WorldTransformResetSystem : public System<WorldTransformResetSystem, WorldTransformComponent>
{
    static void ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms)
    {
        for (auto& worldTransform : worldTransforms)
        {
            worldTransform.transform.Reset();
        }
    }   
};

struct WorldTransformPositionSystem : public System<WorldTransformPositionSystem, WorldTransformComponent, PositionComponent>
{
    static void ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms, std::vector<PositionComponent>& positions)
    {
        VERIFY(worldTransforms.size() == positions.size());
        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            worldTransforms[index].transform.SetPosition(positions[index].position);
        }
    }   
};

struct WorldTransformScaleSystem : public System<WorldTransformScaleSystem, WorldTransformComponent, ScaleComponent>
{
    static void ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms, std::vector<ScaleComponent>& scales)
    {
        VERIFY(worldTransforms.size() == scales.size());
        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            worldTransforms[index].transform.SetScale(scales[index].scale);
        }
    }   
};

struct WorldTransformRotationSystem : public System<WorldTransformRotationSystem, WorldTransformComponent, RotationComponent>
{
    static void ApplyToArchetype(std::vector<WorldTransformComponent>& worldTransforms, std::vector<RotationComponent>& rotations)
    {
        VERIFY(worldTransforms.size() == rotations.size());
        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            worldTransforms[index].transform.SetRotation(rotations[index].rotation);
        }
    }   
};

struct LocalToWorldTransformSystem : public System<LocalToWorldTransformSystem>
{
    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<const std::vector<EntityId>>> allEntities;
        std::vector<Core::Ptr<std::vector<WorldTransformComponent>>> allWorldTransforms;
        std::vector<Core::Ptr<std::vector<LocalTransformComponent>>> allLocalTransforms;
        std::vector<Core::Ptr<std::vector<ParentComponent>>> allParents;

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent>();
        for (auto& archetype : affectedArchetypes)
        {
            allEntities.emplace_back(&archetype->GetEntities());
            allWorldTransforms.emplace_back(&(archetype->GetComponents<WorldTransformComponent>()));
            allLocalTransforms.emplace_back(archetype->HasComponent<LocalTransformComponent>() ? &(archetype->GetComponents<LocalTransformComponent>()) : nullptr);
            allParents.emplace_back(archetype->HasComponent<ParentComponent>() ? &(archetype->GetComponents<ParentComponent>()) : nullptr);
        }

        // Verify that all entities list and all world transform lists are equal in size (check assumptions) IN DEBUG ONLY

        // sort to make sure all parent world transforms are calculated first so dependents can assume completion
        static constexpr size_t INVALID_INDEX = size_t(0) - 1;
        // vector of <entity location, dependency location>
        std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> dependencyTree;
        // initialize
        auto findParent = [&allParents](const std::pair<size_t, size_t>& location) -> Core::Ptr<ParentComponent>
        {
            auto parents = allParents[location.first];
            if (parents == nullptr)
            {
                return nullptr;
            }
            
            return &((*parents)[location.second]);
        };
        auto findParentIndices = [&allEntities](const ParentComponent& parent)
        {
            size_t firstIndex = 0;
            size_t secondIndex = 0;

            for (; firstIndex < allEntities.size(); ++firstIndex)
            {
                auto& entities = *(allEntities[firstIndex]);
                secondIndex = 0;
                for (; secondIndex < entities.size(); ++secondIndex)
                {
                    if (entities[secondIndex] == parent.entity)
                    {
                        break;
                    }
                }
                if (secondIndex < entities.size())
                {
                    break;
                }
            }

            if (firstIndex >= allEntities.size())
            {
                throw std::exception("Could not find parent!");
            }

            return std::make_pair(firstIndex, secondIndex);
        };
        for (size_t firstIndex = 0; firstIndex < allEntities.size(); ++firstIndex)
        {
            auto entities = *(allEntities[firstIndex]);
            for (size_t secondIndex = 0; secondIndex < entities.size(); ++secondIndex)
            {
                auto entityLocation = std::make_pair(firstIndex, secondIndex);
                auto parent = findParent(entityLocation);
                auto dependencyLocation = (parent != nullptr) ? findParentIndices(*parent) : std::make_pair(INVALID_INDEX, INVALID_INDEX);
                dependencyTree.emplace_back(entityLocation, dependencyLocation);
            }
        }
        // sort based on dependencies
        std::sort(dependencyTree.begin(), dependencyTree.end(), [](const auto& p1, const auto& p2)
        {
            // if p1 depends on p2, p2 must come after
            if (p1.second == p2.first)
            {
                return false;
            }
            // if p2 depends on p1, p1 must come first
            if (p2.second == p1.first)
            {
                return true;
            }

            // if one of them has no dependencies and the other does, the one with no dependencies should go first
            // otherwise, sort based on their indices
            auto invalidPair = std::make_pair(INVALID_INDEX, INVALID_INDEX);
            bool p1_noDeps = p1.second == invalidPair;
            bool p2_noDeps = p2.second == invalidPair;
            if (p1_noDeps == p2_noDeps)
            {
                auto p1_indices = p1.first;
                auto p2_indices = p2.first;
                if (p1_indices.first > p2_indices.first)
                {
                    return false;
                }
                return (p1_indices.first < p2_indices.first ? true : p1_indices.second < p2_indices.second);
            }
            else if (p1_noDeps) // p1_noDeps == true, p2_noDeps == false
            {
                return true;
            }
            else // p1_noDeps == false, p2_noDeps == true
            {
                return false;
            }
        });

        // Note: This is not efficient, we end up jumping around a lot. there isn't much of an alternative (even copying sorted into a new list will result in jumping around)
        // But don't worry about this yet, optimize this later once we know it works
        // actually update
        for (const auto& dependencySet : dependencyTree)
        {
            // no dependency means it does not have a local transform, means the world transform is as-is
            if (dependencySet.second == std::make_pair(INVALID_INDEX, INVALID_INDEX))
            {
                continue;
            }

            auto& parentWorldTransform = (*(allWorldTransforms[dependencySet.second.first]))[dependencySet.second.second];

            auto& thisLocalTransform = (*(allLocalTransforms[dependencySet.first.first]))[dependencySet.first.second];

            auto& thisWorldTransform = (*(allWorldTransforms[dependencySet.first.first]))[dependencySet.first.second];
            thisWorldTransform.transform = thisLocalTransform.transform.GetTransformationMatrix() * parentWorldTransform.transform.GetTransformationMatrix();
        }
    }
};

// executed in the order provided
// Note: we are doing some heavy duplication of code, we are updating the WorldTransformComponent even for entities with LocalTransformComponents, which means we are iterating over those entities twice
struct TransformSystem : public CompoundSystem<TransformSystem,
WorldTransformResetSystem,
WorldTransformPositionSystem,
WorldTransformScaleSystem,
WorldTransformRotationSystem,
LocalTransformResetSystem,
LocalTransformPositionSystem,
LocalTransformScaleSystem,
LocalTransformRotationSystem,
LocalToWorldTransformSystem>
{
    // maybe want custom logic to handle dependency for parallel execution?
};
}// namespace Application