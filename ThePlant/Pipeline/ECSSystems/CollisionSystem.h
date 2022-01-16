#pragma once

#include "Pipeline/Collision/ColliderComponents.h"
#include "Pipeline/Collision/Collision.h"
#include "Pipeline/Collision/OctTree.h"

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application
{
struct CollisionTreeBuildingSystem: public System<CollisionTreeBuildingSystem>
{
    CollisionSystem(Collision::OctTree& octTree)
    , _octTree(octTree)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        _octTree.ClearTree();

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<WorldTransformComponent, ColliderComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(archetype->GetEntities(), archetype->GetComponents<WorldTransformComponent>, archetype->GetComponents<ColliderComponent>());
        }
    }

private:
    Collision::OctTree& _octTree;

    void _ApplyToArchetype(std::vector<Entity>& entities, std::vector<WorldTransformComponent>& worldTransforms, std::vector<ColliderComponent>& colliderComponents) const
    {
        VERIFY(entities.size() == worldTransforms.size());
        VERIFY(worldTransforms.size() == colliderComponents.size());

        for (size_t index = 0; index < worldTransforms.size(); ++index)
        {
            ShapeOrientation3D colliderOrientation = { worldTransforms[index].transform, colliderComponents[index].shape };
            _octTree.AddContent({ colliderOrientation, entities[index] });
        }
    }
};

struct CollisionHandlingSystem : System<CollisionHandlingSystem>
{
    CollisionHandlingSystem(Collision::CollisionManager& collisionManager)
    , _collisionManager(collisionManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        auto& allCollisions = _collisionManager.GetAllCollisions();
        const auto& allCollisionHandlgers = _collisionManager.GetAllCollisionHandlers();

        for (auto& handler : allCollisionHandlgers)
        {
            _HandleCollisions(handler, allCollisions);
        }
    }

private:
    CollisionManager& _collisionManager;

    void _HandleCollisions(const Collision::ICollisionHandler& handler, std::vector<Collision::Collision>& allCollisions)
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
        CollisionHandlingSystem>(collisionManager.GetOctTree(), collisionManager)
    {}
};
} // namespace Application