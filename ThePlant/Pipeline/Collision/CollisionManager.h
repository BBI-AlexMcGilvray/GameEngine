#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Core/IdTypes/InstanceId.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/Collision/OctTree.h"
#include "Pipeline/ECS/DataOriented/ECS.h"

namespace Application
{
namespace Collision
{
struct CollisionManager
{
    CollisionManager(ECS& ecs, const Core::Math::Float3& worldSize);

    OctTree& GetOctTree();
    std::vector<Collision> GetAllCollisions() const;

    const std::vector<Core::Ptr<ICollisionHandler>> GetAllCollisionHandlers() const;
    
    template <typename T, typename ...ARGS>
    Core::instanceId<ICollisionHandler> AddCollisionHandler(ARGS&& ...args)
    {
        return AddCollisionHandler(std::make_unique<T>(std::forward<ARGS>(args)....));
    }
    Core::instanceId<ICollisionHandler> AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler);

private:
    OctTree _octTree;
    std::unordered_map<Core::instanceId<ICollisionHandler>, std::unique_ptr<ICollisionHandler>, Core::instanceIdHasher<ICollisionHandler>> _handlers;
};
} // namespace Collision
} // namespace Application