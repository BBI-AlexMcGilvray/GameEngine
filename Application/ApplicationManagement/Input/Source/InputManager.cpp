#include "ApplicationManagement/Input/Headers/InputManager.h"

namespace Application {
namespace Input {
  InputManager::InputManager(const SDL2Manager &sdl)
    : SDL(sdl)
  {
  }

  void InputManager::Initialize()
  {
    // create controller logic mapping
    // have controller logic mapping initialize
  }

  void InputManager::Start()
  {
  }

  void InputManager::Update()
  {
    PollSDL();
  }

  void InputManager::End()
  {
  }

  void InputManager::CleanUp()
  {
    // have controller mapping save any changes made during gameplay (?)
  }

  void InputManager::PollSDL()
  {
    // this loop should probably be in the InputManager
    SDL_Event event;
    while (SDL.Poll(event)) {
      switch (event.type) {
      case SDL_QUIT: {
        // send an quit event
        Quit();
        break;
      }
      case SDL_WINDOWEVENT: {
        // pass event to SDL.WindowManager to handle resizing
        break;
      }
      default: {
        if (Controller != nullptr) {
          Controller->HandleInput(CreateInputEvent(event));
        }
        break;
      }
      }
    }
  }
}// namespace Input
}// namespace Application