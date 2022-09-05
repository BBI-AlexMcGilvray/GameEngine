#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Core/IdTypes/InstanceId.h"

#include "Pipeline/Collision/Collisions.h"
#include "Pipeline/Collision/CollisionHandler.h"
#include "Pipeline/Collision/OctTree.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/IDs.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

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
    const OctTree& GetOctTree() const;
    std::vector<StatefulCollision> GetAllCollisions();

    const std::vector<Core::Ptr<ICollisionHandler>> GetAllCollisionHandlers() const;
    
    template <typename T, typename ...ARGS>
    Core::instanceId<ICollisionHandler> AddCollisionHandler(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("Collision");
        return AddCollisionHandler(std::make_unique<T>(std::forward<ARGS>(args)...));
    }
    Core::instanceId<ICollisionHandler> AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler);

    template <typename T>
    void RemoveCollisionHandler()
    {
        size_t index = 0;
        for (auto& handler : _handlers)
        {
            if (handler.second->IsHandler<T>())
            {
                _handlers.erase(handler.first);
                return;
            }
            ++index;
        }
    }
    
private:
    ECS& _ecs;
    OctTree _octTree;
    std::unordered_map<Core::instanceId<ICollisionHandler>, std::unique_ptr<ICollisionHandler>, Core::instanceIdHasher<ICollisionHandler>> _handlers;
    
    // cache the collisions for the given frame
    std::vector<StatefulCollision> _cachedCollisions;
    std::unordered_map<EntityId, std::vector<EntityId>> _existingCollisions;
    bool _frameCached = false;

    std::vector<StatefulCollision> _HandleCollisionStates(std::vector<Collision> collisions);
};
} // namespace Collision
} // namespace Application