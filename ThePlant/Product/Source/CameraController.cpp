#include "Product/Headers/CameraController.h"

namespace Product
{
    CameraController::CameraController()
    : _cameraNode(nullptr)
    {}

    CameraController::CameraController(Core::Ptr<Application::Geometric::CameraNode> cameraNode)
    : _cameraNode(cameraNode)
    {}

    bool CameraController::handleInput(Ptr<const Application::Input::InputEventBase> event) const
    {
        switch (event->getInputEventType())
        {
            case Application::Input::InputEventType::MouseWheelEvent:
            {
                auto actualEvent = static_cast<Core::Ptr<const Application::Input::InputEvent<Application::Input::MouseWheelData>>>(event);

                _cameraNode->Transformation.AdjustPosition(Core::Math::Float3(0.0f, 0.0f, 5.0f) * static_cast<float>(actualEvent->data.mouseX));

                return true;
            }
            default:
            {
                CORE_WARNING("CameraController", "We do not handle this type of input event type");
            }
        }

        return false;
    }
}