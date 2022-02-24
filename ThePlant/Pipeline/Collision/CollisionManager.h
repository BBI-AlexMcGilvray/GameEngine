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

    // should only be called once per frame
    void ResetCollisionCache();
    OctTree& GetOctTree();
    std::vector<Collision> GetAllCollisions();

    const std::vector<Core::Ptr<ICollisionHandler>> GetAllCollisionHandlers() const;
    
    template <typename T, typename ...ARGS>
    Core::instanceId<ICollisionHandler> AddCollisionHandler(ARGS&& ...args)
    {
        return AddCollisionHandler(std::make_unique<T>(std::forward<ARGS>(args)...));
    }
    Core::instanceId<ICollisionHandler> AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler);

    template <typename T>
    void RemoveSystem()
    {
        size_t index = 0;
        for (auto& handler : _handlers)
        {
            if (handler->IsHandler<SYSTEM>())
            {
                _handlers.erase(_handlers.begin() + index);
                return;
            }
            ++index;
        }
    }
    
private:
    OctTree _octTree;
    std::unordered_map<Core::instanceId<ICollisionHandler>, std::unique_ptr<ICollisionHandler>, Core::instanceIdHasher<ICollisionHandler>> _handlers;
    
    // cache the collisions for the given frame
    std::vector<Collision> _cachedCollisions;
    bool _frameCached = false;
};
} // namespace Collision
} // namespace Application