#include "Product/Headers/WorldInteractor.h"

#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"
// debug
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Pipeline/Factory_Temp/EntitySnapshotUIVisitor.h"
// \debug

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/Collision/CollisionUtils.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/LifetimeComponent.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Factory_Temp/Factory.h"
#include "Pipeline/Input/Headers/InputManager.h"

namespace Product
{
    WorldInteractor::WorldInteractor(Application::State& state, const Application::EntityId& cameraEntity)
    : _state(&state)
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
            
            Application::EntitySnapshot cameraSnapshot = _state->ECS().GetTemporaryEntitySnapshot(_cameraEntity);

            SelectObject(cameraSnapshot);
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

    void WorldInteractor::SelectObject(const Application::EntitySnapshot& cameraSnapshot)
    {
        const auto& mouseAxis = _state->InputManager().GetState<Application::Input::AxisState>(Application::Input::MouseAxis::Position);

        // const auto selected = Application::Collision::GetFirstClickedOnAndCreateRay(*_state, mouseAxis, cameraSnapshot, 10.0f);
        const auto selected = Application::Collision::GetFirstClickedOn(*_state, mouseAxis, cameraSnapshot);
        
        // testing visiting entity snapshot
        WITH_DEBUG_SERVICE(Editor::Factory)
        (
            service->SelectEntity(selected.first.GetEntityId());
        )
    }
}