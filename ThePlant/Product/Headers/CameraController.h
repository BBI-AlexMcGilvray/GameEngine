#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/ECS.h"

namespace Product
{
    /*
    This entire this is bad, this is just to test input functionality
    */
    class CameraController : public Application::Input::IInputReceiver
    {
        static inline const Core::Math::Float3 RIGHT = Core::Math::Float3(1.0f, 0.0f, 0.0f);
        static inline const Core::Math::Float3 UP = Core::Math::Float3(0.0f, 1.0f, 0.0f);
        static inline const Core::Math::Float3 FORWARD = Core::Math::Float3(0.0f, 0.0f, 1.0f);

        static inline const Core::Math::FQuaternion LOOK_RIGHT = Core::Math::FQuaternion(Core::Math::FDeg(90.0f), Core::Math::FDeg(0.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_LEFT = Core::Math::FQuaternion(Core::Math::FDeg(-90.0f), Core::Math::FDeg(0.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_UP = Core::Math::FQuaternion(Core::Math::FDeg(0.0f), Core::Math::FDeg(90.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_DOWN = Core::Math::FQuaternion(Core::Math::FDeg(0.0f), Core::Math::FDeg(-90.0f), Core::Math::FDeg(0.0f));

    public:
        CameraController() = default;
        CameraController(Application::ECS& ecs, const Application::EntityId& cameraEntity);

        bool handleInput(Core::Second dt, Ptr<const Application::Input::InputEventBase> event) override;

    private:
        Core::Ptr<Application::ECS> _ecs;
        Application::EntityId _cameraEntity;

        float _moveSpeed = 100.0f;
        float _lookSpeed = 0.1f;

        bool _movingLeft = false;
        bool _movingRight = false;
        bool _movingForward = false;
        bool _movingBack = false;
    };
}