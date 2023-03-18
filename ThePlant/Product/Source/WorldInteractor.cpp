#include "Product/Headers/WorldInteractor.h"

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
            
            Application::EntitySnapshot cameraSnapshot = _state->ECS().GetTemporaryEntitySnapshot(_cameraEntity);

            SelectObject(cameraSnapshot);
        }
    }

    bool WorldInteractor::handleInput(Application::Input::InputEvent& event)
    {
        switch (event.inputEventType)
        {
            case Application::Input::InputEventType::MouseClickedEvent:
            {                
                const Application::Input::MouseClickedData mouseClickedData = std::get<Application::Input::MouseClickedData>(event.inputEventData);

                if (mouseClickedData.button == Application::Input::MouseButton::Left && mouseClickedData.state == Application::Input::ButtonState::Down)
                {
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
        
        WITH_DEBUG_SERVICE(Editor::Factory)
        (
            service->SelectEntity(selected.first.GetEntityId());
        )
    }
}