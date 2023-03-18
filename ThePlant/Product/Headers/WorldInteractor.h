#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Product
{
    /*
    This is to test clicking/selecting things in the world
    */
    class WorldInteractor : public Application::Input::IInputReceiver
    {
        // copied from CameraController, maybe this should be a global define?
        //      * though we may want to differentiate between game-forward (x) and camera-forward (z)
        static inline const Core::Math::Float3 FORWARD = Core::Math::Float3(0.0f, 0.0f, -1.0f);
    public:
        WorldInteractor() = default;
        WorldInteractor(Application::State& state, const Application::EntityId& cameraEntity);

        void Update(Core::Second deltaTime) override;
        bool handleInput(Application::Input::InputEvent& event) override;

    private:
        Core::Ptr<Application::State> _state = nullptr;
        Application::EntityId _cameraEntity;

        bool _doInteraction = false;

        void SelectObject(const Application::EntitySnapshot& cameraSnapshot);
    };
}