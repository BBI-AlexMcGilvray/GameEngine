#include "Pipeline/Collision/CollisionManager.h"

namespace Application
{
namespace Collision
{
CollisionManager::CollisionManager(ECS& ecs, const Core::Math::Float3& worldSize)
: _octTree(CreateOctTree(ecs, worldSize))
, _ecs(ecs)
{}

void CollisionManager::ResetCollisionCache()
{
    _cachedCollisions.clear();
    _frameCached = false;
}

OctTree& CollisionManager::GetOctTree()
{
    return _octTree;
}

std::vector<StatefulCollision> CollisionManager::GetAllCollisions()
{
    if (!_frameCached)
    {
        _cachedCollisions = _HandleCollisionStates(_octTree.AllCollisions()); // we do this here to not pollute the OctTree
        _frameCached = true;
    }
    return _cachedCollisions;
}

const std::vector<Core::Ptr<ICollisionHandler>> CollisionManager::GetAllCollisionHandlers() const
{
    SCOPED_MEMORY_CATEGORY("Collision");
    std::vector<Core::Ptr<ICollisionHandler>> allHandlers;

    for (auto& handler : _handlers)
    {
        allHandlers.push_back(handler.second.get());
    }

    return allHandlers;
}

Core::instanceId<ICollisionHandler> CollisionManager::AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler)
{
    SCOPED_MEMORY_CATEGORY("Collision");
    auto handlerId = Core::GetInstanceId<ICollisionHandler>();

    _handlers.emplace(handlerId, std::move(handler));

    return handlerId;
}

// collision manager is in charge of specifying what collisions existed before vs now
// this is so OctTree is only aware of 'collisions', not any concept of persistence
std::vector<StatefulCollision> CollisionManager::_HandleCollisionStates(std::vector<Collision> collisions)
{
    SCOPED_MEMORY_CATEGORY("Collision");
    std::vector<StatefulCollision> statefulCollisions;
    statefulCollisions.reserve(collisions.size());

    std::unordered_map<EntityId, std::vector<EntityId>> currentCollisions;

    for (auto& collision : collisions)
    {
        EntityId entity1 = collision.entity1.GetEntity();
        EntityId entity2 = collision.entity2.GetEntity();

        CollisionState state = CollisionState::Initial;

        if (const auto entity1Collisions = _existingCollisions.find(entity1); entity1Collisions != _existingCollisions.end())
        {
            if (const auto entity2Iter = std::find(entity1Collisions->second.begin(), entity1Collisions->second.end(), entity2); entity2Iter != entity1Collisions->second.end())
            {
                state = CollisionState::Persisting;

                // remove it from the existing collisions
                entity1Collisions->second.erase(entity2Iter);
                if (entity1Collisions->second.empty())
                {
                    _existingCollisions.erase(entity1);
                }

                // double-indexed map, need to delete both
                const auto entity2Collisions = _existingCollisions.find(entity2);
                entity2Collisions->second.erase(std::find(entity2Collisions->second.begin(), entity2Collisions->second.end(), entity1));
                if (entity2Collisions->second.empty())
                {
                    _existingCollisions.erase(entity2);
                }
            }
        }

        statefulCollisions.push_back({ collision, state });

        currentCollisions[entity1].push_back(entity2);
        currentCollisions[entity2].push_back(entity1);
    }

    std::unordered_map<EntityId, EntitySnapshot> snapshots;
    snapshots.reserve(_existingCollisions.size());
    for (auto completedCollision = _existingCollisions.begin(); completedCollision != _existingCollisions.end(); ++completedCollision)
    {   // getting snapshots here so we only get it once per entity (should be more efficient)
        snapshots[completedCollision->first] = _ecs.GetTemporaryEntitySnapshot(completedCollision->first);
    }

    for (auto completedCollision = _existingCollisions.begin(); completedCollision != _existingCollisions.end();)
    {
        EntityId entity1 = completedCollision->first;

        for (const auto& entity2 : completedCollision->second)
        {
            statefulCollisions.push_back({ snapshots[entity1], snapshots[entity2], Core::Geometric::Point3D(), CollisionState::Complete });

            // remove to not double-count
            _existingCollisions.erase(entity2);
        }

        completedCollision = _existingCollisions.erase(completedCollision);
    }

    _existingCollisions = std::move(currentCollisions);
    return statefulCollisions;
}
} // namespace Collision
} // namespace Application