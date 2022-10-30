#include "Pipeline/Collision/CollisionUtils.h"

#include "Pipeline/ECSSystems/CollisionComponents.h"
#include "Pipeline/ECSSystems/LifetimeComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application
{
namespace Collision
{
    // -1 lifetime -> no lifetime
    EntityHandler CreateRay(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f)
    {
        auto& entityHandler = ecs->CreateEntity();

        entityHandler.AddComponent<Application::PositionComponent>(positionComponent.position);
        // no rotation component because the ray contains the direction
        entityHandler.AddComponent<Application::WorldTransformComponent>();
        entityHandler.AddComponent<Application::ColliderComponent>(ray, true, Application::ColliderState::Dynamic); // trigger so things don't bounce off of it
        if (lifetime != -1.0f)
        {
            entityHandler.AddComponent<Application::LifetimeComponent>(lifetime);
        }

        return entityHandler;
    }

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHit(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray)
    {
        const auto& octTree = state.CollisionManager().GetOctTree();

        Core::Geometric::Orientation orientation(origin)
        Core::Geometric::ShapeOrientation3D raycast(orientation, ray);
        
        return octTree.FindFirstEntity(raycast);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHits(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray)
    {
        const auto& octTree = state.CollisionManager().GetOctTree();

        Core::Geometric::Orientation orientation(origin)
        Core::Geometric::ShapeOrientation3D raycast(orientation, ray);

        return octTree.FindAllEntities(raycast);
    }

#if DEBUG
    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHitAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f)
    {
        CreateRay(state.ECS(), origin, ray, lifetime);
        return GetFristRaycastHit(state, origin, ray);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHitsAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f)
    {
        CreateRay(state.ECS(), origin, ray, lifetime);
        return GetAllRaycastHits(state, origin, ray);
    }
#endif //DEBUG
} // namespace Collision
} // namespace Application