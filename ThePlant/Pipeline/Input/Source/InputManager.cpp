#include "Pipeline/Input/Headers/InputManager.h"

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

  void InputManager::_PollSDL(Core::Second dt)
  {
    SDL_Event event;
    while (_SDL.Poll(event)) {
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
          _HandleEvent(dt, std::move(event));
          break;
        }
      }
    }
  }

  void InputManager::_HandleEvent(Core::Second dt, SDL_Event&& event) const
  {
    if (_controller != nullptr) {
      auto createdEvent = createInputEvent(event); // creating it here so we can do the below check and avoid calling based on null (unhandled) event types
      if (createdEvent != nullptr)
      {
        _controller->handleInput(dt, std::move(createdEvent));
      }
    }
    else
    {
      DEBUG_ERROR("InputManager", "Trying to handle input event without a controller registered");
    }
  }
}// namespace Input
}// namespace Application