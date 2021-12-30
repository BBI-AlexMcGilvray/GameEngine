#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/ECS.h"

namespace Product
{
    /*
    This entire this is bad, this is just to test input functionality
    */
    class CameraController : public Application::Input::IInputReceiver
    {
    public:
        CameraController() = default;
        CameraController(Application::ECS& ecs, const Application::EntityId& cameraEntity);

        bool handleInput(Ptr<const Application::Input::InputEventBase> event) const override;

    private:
        Core::Ptr<Application::ECS> _ecs;
        Application::EntityId _cameraEntity;
    };
}