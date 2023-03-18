#include "Pipeline/Input/Headers/InputManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Dependencies/IMGUI/backends/imgui_impl_sdl.h"

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

#ifdef MULTITHREADED_RENDERING
  void InputManager::ThreadedUpdate()
  {
    DEBUG_PROFILE_SCOPE("InputManager::ThreadedUpdate");
    _PollSDL();
  }
#endif

  void InputManager::update(Core::Second dt)
  {
    DEBUG_PROFILE_SCOPE("InputManager::update");
  #ifndef MULTITHREADED_RENDERING
    /*
    if we do this with a rendering thread:
      * polls sdl for all relevant events
      * that thread is in charge of converting sdl event -> internal events
      * queueing those events internally to be queuried by the game logic thread
    the game logic thread:
      * polls the internal events
      * updates the states then handles the events
    */
    _PollSDL();
  #endif
    _PollInternal(dt);
  }

  void InputManager::end()
  {
  }

  void InputManager::cleanUp()
  {
    // have controller mapping save any changes made during gameplay (?)
  }

  std::unique_lock<std::mutex> InputManager::_GetLock() { return std::unique_lock<std::mutex>(_internalEventsMutex); }

  void InputManager::_PollSDL()
  {
    SCOPED_MEMORY_CATEGORY("Input");

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
          _QueueNewEvent(std::move(event));
          break;
        }
      }
    }

    _InternalizeNewEvents();
  }

  void InputManager::_QueueNewEvent(SDL_Event&& sdlEvent)
  {
    auto internalEvent = CreateInputEvent(sdlEvent);
    const auto& io = ImGui::GetIO();
    
    switch(internalEvent.inputEventType)
    {
      case InputEventType::KeyboardEvent:
      {
        if (!io.WantCaptureKeyboard)
        {
          _eventsToBeInternalized.emplace_back(internalEvent);
        }
        return;
      }
      case InputEventType::MouseClickedEvent:
      case InputEventType::MouseMovedEvent:
      case InputEventType::MouseWheelEvent:
      {
        if (!io.WantCaptureMouse)
        {
          _eventsToBeInternalized.emplace_back(internalEvent);
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

  void InputManager::_InternalizeNewEvents()
  {
    auto lock = _GetLock();
    _internalEvents.insert(_internalEvents.end(), _eventsToBeInternalized.begin(), _eventsToBeInternalized.end());
    lock.unlock();
    
    _eventsToBeInternalized.clear();
  }
  
  void InputManager::_PollInternal(Core::Second deltaTime)
  {
    SCOPED_MEMORY_CATEGORY("InputManager");
    auto lock = _GetLock();

    for (auto& internalEvent : _internalEvents)
    {
      _HandleEvent(std::move(internalEvent));
      _controller->Update(deltaTime);
    }

    _internalEvents.clear();
  }

  void InputManager::_HandleEvent(InputEvent&& internalEvent)
  {
    _UpdateState(internalEvent);

    auto& io = ImGui::GetIO();
    if (_controller != nullptr)
    {
      _controller->handleInput(std::move(internalEvent));
    }
    else
    {
      DEBUG_ERROR("InputManager", "Trying to handle input event without a controller registered");
    }
  }

  void InputManager::_UpdateState(const InputEvent& internalEvent)
  {
    switch(internalEvent.inputEventType)
    {
      case InputEventType::KeyboardEvent:
      {
        const KeyboardButtonData keyboardData = std::get<KeyboardButtonData>(internalEvent.inputEventData);

        _state.SetState(keyboardData.button, keyboardData.state);
        return;
      }
      case InputEventType::MouseClickedEvent:
      {
        const MouseClickedData mouseClickData = std::get<MouseClickedData>(internalEvent.inputEventData);

        // should we be handling the other data?
        _state.SetState(mouseClickData.button, mouseClickData.state);
        return;
      }
      case InputEventType::MouseMovedEvent:
      {
        const MouseMovedData mouseMovedData = std::get<MouseMovedData>(internalEvent.inputEventData);

        AxisState mouseState { { mouseMovedData.mouseX, mouseMovedData.mouseY }, { mouseMovedData.deltaX, mouseMovedData.deltaY } };
        _state.SetState(MouseAxis::Position, mouseState);
        return;
      }
      case InputEventType::MouseWheelEvent:
      {
        const MouseWheelData mouseWheelData = std::get<MouseWheelData>(internalEvent.inputEventData);

        const Core::Math::Int2 current = { mouseWheelData.mouseX, mouseWheelData.mouseY };
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