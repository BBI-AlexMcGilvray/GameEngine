#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Pipeline/Geometric/Headers/CameraNode.h"

namespace Product
{
    /*
    This entire this is bad, this is just to test input functionality
    */
    class CameraController : public Application::Input::IInputReceiver
    {
    public:
        CameraController();
        CameraController(Core::Ptr<Application::Geometric::CameraNode> cameraNode);

        bool handleInput(Ptr<const Application::Input::InputEventBase> event) const override;
    private:
        Core::Ptr<Application::Geometric::CameraNode> _cameraNode;
    };
}