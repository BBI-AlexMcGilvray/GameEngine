#pragma once

#include "Pipeline/Collision/Collisions.h"
#include "Pipeline/Collision/CollisionHandler.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"

namespace Product
{
namespace Testing
{
struct CollisionCountComponent
{
    int collisions;
    
    CollisionCountComponent() = default;
    CollisionCountComponent(const CollisionCountComponent&) = default;
    CollisionCountComponent(CollisionCountComponent&&) = default;
    CollisionCountComponent& operator=(const CollisionCountComponent&) = default;
    CollisionCountComponent& operator=(CollisionCountComponent&&) = default;

    CollisionCountComponent(int collisions)
    : collisions(collisions)
    {}

    bool operator==(const CollisionCountComponent& other) const
    {
        return collisions == other.collisions;
    }
    bool operator !=(const CollisionCountComponent& other) const { return !(*this == other); }
};

struct DestroyOnCollisionComponent
{    
    DestroyOnCollisionComponent() = default;
    DestroyOnCollisionComponent(const DestroyOnCollisionComponent&) = default;
    DestroyOnCollisionComponent(DestroyOnCollisionComponent&&) = default;
    DestroyOnCollisionComponent& operator=(const DestroyOnCollisionComponent&) = default;
    DestroyOnCollisionComponent& operator=(DestroyOnCollisionComponent&&) = default;

    bool operator==(const DestroyOnCollisionComponent& other) const
    {
        return true;
    }
    bool operator !=(const DestroyOnCollisionComponent& other) const { return !(*this == other); }
};

struct CountedCollision : public Application::Collision::CollisionHandler<CountedCollision>
{
    CountedCollision(Application::ECS& ecs)
    : Application::Collision::CollisionHandler<CountedCollision>("CountedCollision", BitmaskEnum<Application::Collision::CollisionState>(Application::Collision::CollisionState::Initial), Application::CollectTypes<CollisionCountComponent>(), Application::TypeCollection(), true)
    , _ecs(ecs)
    {} // don't need to handle both separately as this is an identical calculation

private:
    Application::ECS& _ecs;

    void _Apply(const Application::Collision::CollisionState collisionState, const Core::Geometric::Point3D& collisionPoint, Application::EntitySnapshot& from, Application::EntitySnapshot& to) const override
    {
        CollisionCountComponent& collisionCount = from.GetComponent<CollisionCountComponent>();
        collisionCount.collisions -= 1;

        if (collisionCount.collisions <= 0)
        {
            std::hash<Application::EntityId> hasher;
            CORE_LOG("TestSystem", "Next collision will destroy " + std::to_string(hasher(from.GetEntityId())));
            _ecs.RemoveComponent<CollisionCountComponent>(from.GetEntityId()).AddComponent<DestroyOnCollisionComponent>();
        }
    }
};

struct DestructiveCollision : public Application::Collision::CollisionHandler<DestructiveCollision>
{
    DestructiveCollision(Application::ECS& ecs)
    : Application::Collision::CollisionHandler<DestructiveCollision>("DestructiveCollision", BitmaskEnum<Application::Collision::CollisionState>(Application::Collision::CollisionState::Initial), Application::CollectTypes<DestroyOnCollisionComponent>(), Application::TypeCollection(), true)
    , _ecs(ecs)
    {} // don't need to handle both separately as this is an identical calculation

private:
    Application::ECS& _ecs;

    void _Apply(const Application::Collision::CollisionState collisionState, const Core::Geometric::Point3D& collisionPoint, Application::EntitySnapshot& from, Application::EntitySnapshot& to) const override
    {
        std::hash<Application::EntityId> hasher;
        CORE_LOG("TestSystem", "Destroying " + std::to_string(hasher(from.GetEntityId())));
        _ecs.RemoveEntity(from.GetEntityId());
    }
};
} // namespace Testing
} // namespace Product