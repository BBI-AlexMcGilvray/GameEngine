#pragma once

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/Collision/OctTree.h"

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

/*
    - To make sure this is more clear and easily debuggable, we should put in a 'frame-step' debug option to allow us to step through 1 frame at a time if desired
        - The render loop can keep running if needed (using the last frame?)
        - If we can have the systems keep running but not apply further changes, that would be ideal for testing out/hitting breakpoints repeatedly
*/
namespace Application
{
struct CollisionTreeBuildingSystem: public System<CollisionTreeBuildingSystem>
{
    CollisionTreeBuildingSystem(Collision::OctTree& octTree)
    : System<CollisionTreeBuildingSystem>("CollisionTreeBuildingSystem")
    , _octTree(octTree)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        _octTree.ClearTree();

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent, ColliderComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype->GetEntities(), archetype->GetComponents<WorldTransformComponent>(), archetype->GetComponents<ColliderComponent>());
        }
    }

private:
    Collision::OctTree& _octTree;

    void _ApplyToArchetype(const std::vector<EntityId>& entities, std::vector<WorldTransformComponent>& worldTransforms, std::vector<ColliderComponent>& colliderComponents) const
    {
        VERIFY(entities.size() == worldTransforms.size());
        VERIFY(worldTransforms.size() == colliderComponents.size());

        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            Core::Geometric::ShapeOrientation3D colliderOrientation = { worldTransforms[index].transform, colliderComponents[index].shape };
            _octTree.AddContent({ colliderOrientation, entities[index] });
        }
    }
};

struct CollisionHandlingSystem : System<CollisionHandlingSystem>
{
    CollisionHandlingSystem(Collision::CollisionManager& collisionManager)
    : System<CollisionHandlingSystem>("CollisionHandlingSystem")
    , _collisionManager(collisionManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        auto& allCollisions = _collisionManager.GetAllCollisions();
        const auto& allCollisionHandlgers = _collisionManager.GetAllCollisionHandlers();

        for (auto& handler : allCollisionHandlgers)
        {
            _HandleCollisions(*handler, allCollisions);
        }
    }

private:
    Collision::CollisionManager& _collisionManager;

    void _HandleCollisions(const Collision::ICollisionHandler& handler, std::vector<Collision::Collision>& allCollisions) const
    {
        for (auto& collision : allCollisions)
        {
            handler.Handle(collision);
        }
    }
};

struct CollisionSystem : public CompoundSystem<CollisionSystem,
CollisionTreeBuildingSystem,
CollisionHandlingSystem>
{
    CollisionSystem(Collision::CollisionManager& collisionManager)
    : CompoundSystem<CollisionSystem,
        CollisionTreeBuildingSystem,
        CollisionHandlingSystem>("CollisionSystem", collisionManager.GetOctTree(), collisionManager)
    {}
};
} // namespace Application