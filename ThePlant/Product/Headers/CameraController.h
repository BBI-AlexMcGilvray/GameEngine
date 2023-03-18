#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/Input/Headers/InputManager.h"

namespace Product
{
    /*
    This entire thing is bad, this is just to test input functionality
        ** maybe not so bad anymore?
    */
    class CameraController : public Application::Input::IInputReceiver
    {
        static inline const Core::Math::Float3 RIGHT = Core::Math::Float3(1.0f, 0.0f, 0.0f);
        static inline const Core::Math::Float3 UP = Core::Math::Float3(0.0f, 1.0f, 0.0f);
        static inline const Core::Math::Float3 FORWARD = Core::Math::Float3(0.0f, 0.0f, 1.0f);

        static inline const Core::Math::FQuaternion LOOK_RIGHT = Core::Math::FQuaternion(Core::Math::FDeg(0.0f), Core::Math::FDeg(90.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_LEFT = Core::Math::FQuaternion(Core::Math::FDeg(0.0f), Core::Math::FDeg(-90.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_UP = Core::Math::FQuaternion(Core::Math::FDeg(90.0f), Core::Math::FDeg(0.0f), Core::Math::FDeg(0.0f));
        static inline const Core::Math::FQuaternion LOOK_DOWN = Core::Math::FQuaternion(Core::Math::FDeg(-90.0f), Core::Math::FDeg(0.0f), Core::Math::FDeg(0.0f));

    public:
        CameraController() = default;
        CameraController(const Application::Input::InputManager& inputManager, Application::ECS& ecs, const Application::EntityId& cameraEntity);

        void Update(Core::Second deltaTime) override;
        bool handleInput(Application::Input::InputEvent& event) override;

    private:
        Core::Ptr<const Application::Input::InputManager> _inputManager;
        Core::Ptr<Application::ECS> _ecs;
        Application::EntityId _cameraEntity;
        Core::Math::FQuaternion _horizontalLook;
        Core::Math::FQuaternion _verticalLook;

        float _moveSpeed = 100.0f;
        float _lookSpeed = 0.1f;

        bool _movingLeft = false;
        bool _movingRight = false;
        bool _movingForward = false;
        bool _movingBack = false;
    };
}