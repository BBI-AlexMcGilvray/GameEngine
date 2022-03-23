#include "Pipeline/Collision/CollisionManager.h"

namespace Application
{
namespace Collision
{
CollisionManager::CollisionManager(ECS& ecs, const Core::Math::Float3& worldSize)
: _octTree(CreateOctTree(ecs, worldSize))
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

std::vector<Collision> CollisionManager::GetAllCollisions()
{
    if (!_frameCached)
    {
        _cachedCollisions = _octTree.AllCollisions();
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
} // namespace Collision
} // namespace Application