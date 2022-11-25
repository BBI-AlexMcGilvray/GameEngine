#include "Pipeline/Input/Headers/InputManager.h"

// testing
#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"
// \testing

namespace Application {
namespace Input {
  InputManager::InputManager(const SDL2Manager &sdl)
    : _SDL(sdl)
    , _controller(nullptr)
  {
  }

  Ptr<IInputController> InputManager::operator->()
  {
    return _controller.get();
  }

  void InputManager::initialize()
  {
    // create controller logic mapping
    // have controller logic mapping initialize
  }

  void InputManager::start()
  {
  }

  void InputManager::setInputController(UniquePtr<IInputController> controller)
  {
    _controller = std::move(controller);
  }

  void InputManager::update(Core::Second dt)
  {
    _PollSDL(dt);
  }

  void InputManager::end()
  {
  }

  void InputManager::cleanUp()
  {
    // have controller mapping save any changes made during gameplay (?)
  }

  void InputManager::_PollSDL(Core::Second deltaTime)
  {
    SDL_Event event;
    while (_SDL.Poll(event)) {
      // SEE: https://marcelfischer.eu/blog/2019/imgui-in-sdl-opengl/
      // other reference: https://github.com/ocornut/imgui/issues/4664
      ImGui_ImplSDL2_ProcessEvent(&event); // pass all events to IMGUI, then handle ourselves (based on IMGUI flags)
      switch (event.type) {
        case SDL_QUIT: {
          // send a quit event
          Quit();
          break;
        }
        case SDL_WINDOWEVENT: {
          // pass event to SDLWindowManager to handle resizing
          break;
        }
        default: {
          _HandleEvent(std::move(event));
          break;
        }
      }
    }
    _controller->Update(deltaTime);
  }

  void InputManager::_HandleEvent(SDL_Event&& event)
  {
    auto createdEvent = createInputEvent(event); // creating it here so we can do the below check and avoid calling based on null (unhandled) event types
    if (createdEvent != nullptr)
    {
      _UpdateState(*createdEvent);

      auto& io = ImGui::GetIO();
      if (_controller != nullptr)
      {
        switch(createdEvent->getInputEventType())
        {
          case InputEventType::KeyboardEvent:
          {
            if (!io.WantCaptureKeyboard)
            {
              _controller->handleInput(std::move(createdEvent)); // we probably still want this for event-driven handlers (like UI?)
            }
            return;
          }
          case InputEventType::MouseClickedEvent:
          case InputEventType::MouseMovedEvent:
          case InputEventType::MouseWheelEvent:
          {
            if (!io.WantCaptureMouse)
            {
              _controller->handleInput(std::move(createdEvent)); // we probably still want this for event-driven handlers (like UI?)
            }
            return;
          }
          case InputEventType::Undetermined:
          default:
          {
            DEBUG_ERROR("InputManager", "No state for this event type");
          }
        }
      }
      else
      {
        DEBUG_ERROR("InputManager", "Trying to handle input event without a controller registered");
      }
    }
    else
    {
      DEBUG_ERROR("InputManager", "Unable to create an event for the given SDL event");
    }
  }

  void InputManager::_UpdateState(const InputEventBase& event)
  {
    switch(event.getInputEventType())
    {
      case InputEventType::KeyboardEvent:
      {
        const InputEvent<KeyboardButtonData>& actualEvent = static_cast<const InputEvent<KeyboardButtonData>&>(event);

        _state.SetState(actualEvent.data.button, actualEvent.data.state);
        return;
      }
      case InputEventType::MouseClickedEvent:
      {
        const InputEvent<MouseClickedData>& actualEvent = static_cast<const InputEvent<MouseClickedData>&>(event);

        // should we be handling the other data?
        _state.SetState(actualEvent.data.button, actualEvent.data.state);
        return;
      }
      case InputEventType::MouseMovedEvent:
      {
        const InputEvent<MouseMovedData>& actualEvent = static_cast<const InputEvent<MouseMovedData>&>(event);

        AxisState mouseState { { actualEvent.data.mouseX, actualEvent.data.mouseY }, { actualEvent.data.deltaX, actualEvent.data.deltaY } };
        _state.SetState(MouseAxis::Position, mouseState);
        return;
      }
      case InputEventType::MouseWheelEvent:
      {
        const InputEvent<MouseWheelData>& actualEvent = static_cast<const InputEvent<MouseWheelData>&>(event);

        const Core::Math::Int2 current = { actualEvent.data.mouseX, actualEvent.data.mouseY };
        const Core::Math::Int2 delta = _state.GetState<AxisState>(MouseAxis::Wheel).position - current;
        AxisState wheelState = { current, delta };
        _state.SetState(MouseAxis::Wheel, wheelState);
        return;
      }
      case InputEventType::Undetermined:
      default:
      {
        DEBUG_ERROR("InputManager", "No state for this event type");
      }
    }
  }
}// namespace Input
}// namespace Application