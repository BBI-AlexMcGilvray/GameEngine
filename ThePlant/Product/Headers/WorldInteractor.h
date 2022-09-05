#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/Input/Headers/InputManager.h"

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
        WorldInteractor(const Application::Input::InputManager& inputManager,  const Application::Collision::CollisionManager& collisionManager, Application::ECS& ecs, const Application::EntityId& cameraEntity);

        void Update(Core::Second deltaTime) override;
        bool handleInput(Ptr<const Application::Input::InputEventBase> event) override;

    private:
        Core::Ptr<const Application::Input::InputManager> _inputManager;
        Core::Ptr<const Application::Collision::CollisionManager> _collisionManager;
        Core::Ptr<Application::ECS> _ecs;
        Application::EntityId _cameraEntity;

        bool _doInteraction = false;

        void SelectObject(const Application::EntitySnapshot& cameraSnapshot);
    };
}