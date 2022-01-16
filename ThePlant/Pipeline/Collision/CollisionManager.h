#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Core/IdTypes/InstanceId.h"

#include "Pipeline/Collision/Collision.h"
#include "Pipeline/Collision/OctTree.h"

namespace Application
{
namespace Collision
{
struct CollisionManager
{
    CollisionManager(const Core::Math::Float3& worldSize);

    OctTree& GetOctTree();
    std::vector<Collision> GetAllCollisions() const;

    const std::vector<Core::Ptr<ICollisionHandler>> GetAllCollisionHandlers() const;
    
    template <typename T, typename ...ARGS>
    Core::InstanceId<ICollisionHandler> AddCollisionHandler(ARGS&& ...args)
    {
        return AddCollisionHandler(std::make_unique<T>(std::forward<ARGS>(args)....));
    }
    Core::InstanceId<ICollisionHandler> AddCollisionHandler(std::unique_ptr<ICollisionHandler> handler);

private:
    OctTree _octTree;
    std::unordered_map<Core::InstanceId<ICollisionHandler>, std::unique_ptr<ICollisionHandler>, instanceIdHasher<ICollisionHandler>> _handlers;
};
} // namespace Collision
} // namespace Application