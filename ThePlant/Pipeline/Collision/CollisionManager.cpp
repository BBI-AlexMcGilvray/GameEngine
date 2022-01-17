#include "Pipeline/Collision/CollisionManager.h"

namespace Application
{
namespace Collision
{
CollisionManager::CollisionManager(ECS& ecs, const Core::Math::Float3& worldSize)
: _octTree(CreateOctTree(ecs, worldSize))
{}

OctTree& CollisionManager::GetOctTree()
{
    return _octTree;
}

std::vector<Collision> CollisionManager::GetAllCollisions() const
{
    return _octTree.AllCollisions();
}

const std::vector<Core::Ptr<ICollisionHandler>> CollisionManager::GetAllCollisionHandlers() const
{
    std::vector<Core::Ptr<ICollisionHandler>> allHandlers;

    for (auto& handler : _handlers)
    {
        allHandlers.push_back(handler.second.get());
    }

    return allHandlers;
}

Core::instanceId<ICollisionHandler> CollisionManager::AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler)
{
    auto handlerId = Core::GetInstanceId<ICollisionHandler>();

    _handlers.emplace(handlerId, std::move(handler));

    return handlerId;
}
} // namespace Collision
} // namespace Application