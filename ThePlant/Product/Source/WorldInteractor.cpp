#include "Product/Headers/WorldInteractor.h"

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
    WorldInteractor::WorldInteractor(const Application::Input::InputManager& inputManager, Application::ECS& ecs, const Application::EntityId& cameraEntity)
    : _inputManager(&inputManager)
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
}