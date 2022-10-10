#include "Product/Headers/WorldInteractor.h"

#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"
// debug
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"
// \debug

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/LifetimeComponent.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Product
{
    WorldInteractor::WorldInteractor(const Application::Input::InputManager& inputManager, const Application::Collision::CollisionManager& collisionManager, Application::ECS& ecs, const Application::EntityId& cameraEntity)
    : _inputManager(&inputManager)
    , _collisionManager(&collisionManager)
    , _ecs(&ecs)
    , _cameraEntity(cameraEntity)
    {
        // make sure entity has position and camera
    }

    /*
    * NOTE: we want to do the interaction ONCE for a click
    * 
    * PROBLEM: The 'Update' and 'handleInput' functions may be run BEFORE the ECS system is updated -> executing interactions may be problematic?
    *   * HOWEVER: the collisiders should be cached, so we should be able to click on them as we would expect.
    *       - selecting things that aren't colliders (just things that have a position) should be doable, but we may need to iterate over all entities that have a location
    *           in a 'custom system' of sorts
    */
    void WorldInteractor::Update(Core::Second deltaTime)
    {
        if (_doInteraction)
        {
            _doInteraction = false;
            CORE_LOG("WorldInteractor", "Executing Event");
            
            Application::EntitySnapshot cameraSnapshot = _ecs->GetTemporaryEntitySnapshot(_cameraEntity);

            SelectObject(cameraSnapshot);
        }
    }

    bool WorldInteractor::handleInput(Ptr<const Application::Input::InputEventBase> event)
    {
        switch (event->getInputEventType())
        {
            case Application::Input::InputEventType::MouseClickedEvent:
            {                
                auto actualEvent = static_cast<Core::Ptr<const Application::Input::InputEvent<Application::Input::MouseClickedData>>>(event);

                if (actualEvent->data.button == Application::Input::MouseButton::Left && actualEvent->data.state == Application::Input::ButtonState::Down)
                {
                    CORE_LOG("WorldInteractor", "Clicked Event");
                    _doInteraction = true;
                    return true;
                }
            }
        }
        return false;
    }

    void WorldInteractor::SelectObject(const Application::EntitySnapshot& cameraSnapshot)
    {
        const Application::CameraComponent& cameraComponent = cameraSnapshot.GetComponent<Application::CameraComponent>();
        const Application::PositionComponent& positionComponent = cameraSnapshot.GetComponent<Application::PositionComponent>();
        const Application::RotationComponent& rotationComponent = cameraSnapshot.GetComponent<Application::RotationComponent>();

        const auto& mouseAxis = _inputManager->GetState<Application::Input::AxisState>(Application::Input::MouseAxis::Position);
        const auto& mousePosition = mouseAxis.position;

        const auto& octTree = _collisionManager->GetOctTree();

        Core::Geometric::Orientation orientation(positionComponent.position, rotationComponent.rotation);
        // 'forward' needs to be calculated then offset by the mouse position
        Core::Geometric::Line3D ray(FORWARD * 100.0f, true); // we probably want it to be infinite in reality?
        Core::Geometric::ShapeOrientation3D raycast(orientation, ray);
        const auto selected = octTree.FindFirstEntity(raycast);

        // create the raycast to help debug
        // auto& entityHandler = _ecs->CreateEntity();
        // entityHandler.AddComponent<Application::PositionComponent>(positionComponent.position);
        // entityHandler.AddComponent<Application::RotationComponent>(rotationComponent.rotation);
        // entityHandler.AddComponent<Application::WorldTransformComponent>();
        // entityHandler.AddComponent<Application::LifetimeComponent>(0.5f); // how long we want the raycast to last
        // entityHandler.AddComponent<Application::ColliderComponent>(ray, true, Application::ColliderState::Dynamic); // trigger so things don't bounce off of it

        // Why does the FIRST raycast after moving the camera always return 0,0,0?
        // why does the FIRST raycast intersect, but none of the others? collision system not handling rays properly?
        CORE_LOG("WorldInteractor", "First interaction at point " + Core::Math::VectorString(selected.second));
    }
}