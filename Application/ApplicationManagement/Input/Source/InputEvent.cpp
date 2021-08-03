#include "ApplicationManagement/Input/Headers/InputEvent.h"

namespace Application {
namespace Input {
  UniquePtr<const InputEventBase> CreateInputEvent(const SDL_Event &sdlEvent)
  {
    switch (sdlEvent.type) {
    case SDL_KEYDOWN: {
      return MakeUnique<InputEvent<KeyboardButtonData>>(InputEventType::KeyboardEvent, sdlEvent.key.timestamp, sdlEvent.key.windowID, GetKeyboardButton(sdlEvent.key.keysym.sym), GetButtonState(sdlEvent.key.type));
    }
    case SDL_MOUSEMOTION: {
      return MakeUnique<InputEvent<MouseMovedData>>(InputEventType::MouseMovedEvent, sdlEvent.key.timestamp, sdlEvent.key.windowID, sdlEvent.motion.x, sdlEvent.motion.y, sdlEvent.motion.xrel, sdlEvent.motion.yrel);
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
      return MakeUnique<InputEvent<MouseClickedData>>(InputEventType::MouseClickedEvent, sdlEvent.key.timestamp, sdlEvent.key.windowID, sdlEvent.motion.x, sdlEvent.motion.y, GetMouseButton(sdlEvent.button.button), GetButtonState(sdlEvent.button.state), sdlEvent.button.clicks);
    }
    case SDL_MOUSEWHEEL: {
      return MakeUnique<InputEvent<MouseWheeledData>>(InputEventType::MouseWheelEvent, sdlEvent.key.timestamp, sdlEvent.key.windowID, sdlEvent.motion.x, sdlEvent.motion.y, sdlEvent.wheel.direction > 0);
    }
    default: {
      return nullptr;
    }
    }
  }
}// namespace Input
}// namespace Application