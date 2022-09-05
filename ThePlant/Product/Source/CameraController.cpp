#include "Product/Headers/CameraController.h"

#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"
// debug
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"
// \debug

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Product
{
    CameraController::CameraController(const Application::Input::InputManager& inputManager, Application::ECS& ecs, const Application::EntityId& cameraEntity)
    : _inputManager(&inputManager)
    , _ecs(&ecs)
    , _cameraEntity(cameraEntity)
    {
        // make sure entity has position and camera
    }

    /*
    * NOTE: problem is this just consumes input, it doesn't get called if there is no NEW input.
    *       this means that if we HOLD a button and there is no new state, the held state is not handled
    *       
    * SO, we need to
    *   - have a handler that tracks the states of each input option
    *       -> global state queryable? or just a generic class that each handler can hold and use?
    *           (this means if that receiver doesn't get input it could be out of sync...)
    *   - update the input
    *       -> if there is a global state above this is probably handled by the 'InputManager'
    *       -> so it would go:
    *           1. poll all events -> set global state
    *           2. tell all active receivers to handle their input state (see below)
    *   - handle the RESULT of that input
    *       -> this should be called regardless of if new input affected those receivers, they should be updated if they are active
    *           * this is to handle the 'button is held' case
    * 
    * NOTE: the above is COMPLETED (just leaving it for potential future cares/info)
    */
    void CameraController::Update(Core::Second deltaTime)
    {
        float dt = Core::Duration(deltaTime);

        Application::EntitySnapshot cameraSnapshot = _ecs->GetTemporaryEntitySnapshot(_cameraEntity);

        Application::CameraComponent& cameraComponent = cameraSnapshot.GetComponent<Application::CameraComponent>();
        Application::PositionComponent& positionComponent = cameraSnapshot.GetComponent<Application::PositionComponent>();
        Application::RotationComponent& rotationComponent = cameraSnapshot.GetComponent<Application::RotationComponent>();

        const Core::Math::FQuaternion cameraFacing = rotationComponent.rotation;
        const Core::Math::Float3 relativeRight = Core::Math::RotateVectorBy(RIGHT, cameraFacing);
        const Core::Math::Float3 relativeForward = Core::Math::RotateVectorBy(FORWARD, cameraFacing);

        // NOTE: reason this looks weird is because we are looking at the same spot and not ROTATING around it, but just moving away and re-focusing
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_W) == Application::Input::ButtonState::Down)
        {
            positionComponent.position -= relativeForward * _moveSpeed * dt;
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_S) == Application::Input::ButtonState::Down)
        {
            positionComponent.position += relativeForward * _moveSpeed * dt;
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_A) == Application::Input::ButtonState::Down)
        {
            positionComponent.position -= relativeRight * _moveSpeed * dt;
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_D) == Application::Input::ButtonState::Down)
        {
            positionComponent.position += relativeRight * _moveSpeed * dt;
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_Space) == Application::Input::ButtonState::Down)
        {
            positionComponent.position += UP * _moveSpeed * dt;
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::KeyboardButton::Button_Control_Left) == Application::Input::ButtonState::Down)
        {
            positionComponent.position -= UP * _moveSpeed * dt;
        }

        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::MouseButton::Right) == Application::Input::ButtonState::Down)
        {
            const auto& mouseAxis = _inputManager->GetState<Application::Input::AxisState>(Application::Input::MouseAxis::Position);

            float deltaX = mouseAxis.delta.X * _lookSpeed * dt;

            _horizontalLook = _horizontalLook * Core::Math::LerpQuat(Core::Math::FQuaternion(), LOOK_LEFT, deltaX);
        }
        if (_inputManager->GetState<Application::Input::ButtonState>(Application::Input::MouseButton::Right) == Application::Input::ButtonState::Down)
        {
            const auto& mouseAxis = _inputManager->GetState<Application::Input::AxisState>(Application::Input::MouseAxis::Position);

            float deltaY = mouseAxis.delta.Y * _lookSpeed * dt;

            _verticalLook = _verticalLook * Core::Math::LerpQuat(Core::Math::FQuaternion(), LOOK_UP, -deltaY);
        }

        // we need to track the horizontal and vertical rotations here so we can always apply them separately
        // otherwise we can get undesired 'roll': https://stackoverflow.com/questions/46738139/prevent-rotation-around-certain-axis-with-quaternion
        rotationComponent.rotation = Core::Math::FQuaternion() * _horizontalLook * _verticalLook;
    }

    bool CameraController::handleInput(Ptr<const Application::Input::InputEventBase> event)
    {
        // not sure if we need to have the event-specific handling if we are just checking state?
        return false;
    }
}