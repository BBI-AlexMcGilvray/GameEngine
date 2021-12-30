#include "Product/Headers/CameraController.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Product
{
    CameraController::CameraController(Application::ECS& ecs, const Application::EntityId& cameraEntity)
    : _ecs(&ecs)
    , _cameraEntity(cameraEntity)
    {}

    bool CameraController::handleInput(Ptr<const Application::Input::InputEventBase> event) const
    {
        switch (event->getInputEventType())
        {
            case Application::Input::InputEventType::MouseWheelEvent:
            {
                auto actualEvent = static_cast<Core::Ptr<const Application::Input::InputEvent<Application::Input::MouseWheelData>>>(event);

                Application::PositionComponent& cameraPosition = _ecs->GetComponentFor<Application::PositionComponent>(_cameraEntity);
                cameraPosition.position += (Core::Math::Float3(0.0f, 0.0f, 5.0f) * static_cast<float>(actualEvent->data.mouseX));

                return true;
            }
            default:
            {
                // can put back in later, just spam at the moment
                //CORE_WARNING("CameraController", "We do not handle this type of input event type");
            }
        }

        return false;
    }
}