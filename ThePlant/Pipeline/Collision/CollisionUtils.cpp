#include "Pipeline/Collision/CollisionUtils.h"

#include "Pipeline/Headers/SDL2Manager.h"
#include "Pipeline/Headers/WindowManager.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/LifetimeComponent.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/Headers/CameraUtils.h"

namespace Application
{
namespace Collision
{
    // -1 lifetime -> no lifetime
    EntityHandler& CreateRay(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime)
    {
        auto& entityHandler = ecs.CreateEntity();

        entityHandler.AddComponent<Application::PositionComponent>(origin);
        // no rotation component because the ray contains the direction
        entityHandler.AddComponent<Application::WorldTransformComponent>();
        entityHandler.AddComponent<Application::ColliderComponent>(ray, true, Application::ColliderState::Dynamic); // trigger so things don't bounce off of it
        if (lifetime != -1.0f)
        {
            entityHandler.AddComponent<Application::LifetimeComponent>(lifetime);
        }

        return entityHandler;
    }

    Core::Geometric::Line3D GetClickRayForCamera(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState)
    {
        const WindowManager& windowManager = state.SDLManager().GetWindowManager();

        const Application::CameraComponent& cameraComponent = cameraState.GetComponent<Application::CameraComponent>();
        const Application::PositionComponent& positionComponent = cameraState.GetComponent<Application::PositionComponent>();
        const Application::RotationComponent& rotationComponent = cameraState.GetComponent<Application::RotationComponent>();
        
        Application::Rendering::Camera cameraCopy = cameraComponent.camera;
        Core::Geometric::Transform transformCopy = cameraState.GetComponent<Application::WorldTransformComponent>().transform;
        Core::Math::Float2 windowSize = Core::Math::Float2(static_cast<float>(windowManager.Width), static_cast<float>(windowManager.Height));
        Core::Math::Float2 mousePosition = Core::Math::Float2(static_cast<float>(mouseState.position.X), static_cast<float>(mouseState.position.Y));

        const auto screenToWorld = Application::Rendering::ScreenToWorld(cameraCopy, transformCopy, mousePosition, windowSize);
        const auto clickDir = screenToWorld - positionComponent.position;
        Core::Geometric::Line3D ray(clickDir * 100.0f, true);

        return ray;
    }

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHit(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray)
    {
        const auto& octTree = state.CollisionManager().GetOctTree();

        Core::Geometric::Orientation orientation(origin);
        Core::Geometric::ShapeOrientation3D raycast(orientation, ray);

        return octTree.FindFirstEntity(raycast);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHits(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray)
    {
        const auto& octTree = state.CollisionManager().GetOctTree();

        Core::Geometric::Orientation orientation(origin);
        Core::Geometric::ShapeOrientation3D raycast(orientation, ray);

        return octTree.FindAllEntities(raycast);
    }

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstClickedOn(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState)
    {
        const Application::PositionComponent& positionComponent = cameraState.GetComponent<Application::PositionComponent>();

        Core::Geometric::Line3D ray = GetClickRayForCamera(state, mouseState, cameraState);
        return GetFirstRaycastHit(state, positionComponent.position, ray);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllClickedOn(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState)
    {
        const Application::PositionComponent& positionComponent = cameraState.GetComponent<Application::PositionComponent>();

        Core::Geometric::Line3D ray = GetClickRayForCamera(state, mouseState, cameraState);
        return GetAllRaycastHits(state, positionComponent.position, ray);
    }

#if DEBUG
    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHitAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime)
    {
        CreateRay(state.ECS(), origin, ray, lifetime);
        return GetFirstRaycastHit(state, origin, ray);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHitsAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime)
    {
        CreateRay(state.ECS(), origin, ray, lifetime);
        return GetAllRaycastHits(state, origin, ray);
    }

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstClickedOnAndCreateRay(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState, const float& lifetime)
    {
        const Application::PositionComponent& positionComponent = cameraState.GetComponent<Application::PositionComponent>();

        Core::Geometric::Line3D ray = GetClickRayForCamera(state, mouseState, cameraState);
        CreateRay(state.ECS(), positionComponent.position, ray, lifetime);
        return GetFirstRaycastHit(state, positionComponent.position, ray);
    }

    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllClickedOnAndCreateRay(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState, const float& lifetime)
    {
        const Application::PositionComponent& positionComponent = cameraState.GetComponent<Application::PositionComponent>();

        Core::Geometric::Line3D ray = GetClickRayForCamera(state, mouseState, cameraState);
        CreateRay(state.ECS(), positionComponent.position, ray, lifetime);
        return GetAllRaycastHits(state, positionComponent.position, ray);
    }
#endif //DEBUG
} // namespace Collision
} // namespace Application