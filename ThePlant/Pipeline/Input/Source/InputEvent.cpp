#include "Pipeline/Input/Headers/InputEvent.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Input {
  UniquePtr<const InputEventBase> createInputEvent(const SDL_Event &sdlEvent)
  {
    /*
    Should we be using 'now', or should we be using sdlEvent.key.timestamp?
    */
    switch (sdlEvent.type) {
    case SDL_KEYDOWN: {
      return MakeUnique<InputEvent<KeyboardButtonData>>(InputEventType::KeyboardEvent,
          Core::TimePoint(Core::SteadyClock::now()),
          sdlEvent.key.windowID,
          getKeyboardButton(sdlEvent.key.keysym.sym),
          getButtonState(sdlEvent.key.type));
    }
    case SDL_MOUSEMOTION: {
      return MakeUnique<InputEvent<MouseMovedData>>(InputEventType::MouseMovedEvent,
          Core::TimePoint(Core::SteadyClock::now()),
          sdlEvent.key.windowID,
          sdlEvent.motion.x,
          sdlEvent.motion.y,
          sdlEvent.motion.xrel,
          sdlEvent.motion.yrel);
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
      return MakeUnique<InputEvent<MouseClickedData>>(InputEventType::MouseClickedEvent,
          Core::TimePoint(Core::SteadyClock::now()),
          sdlEvent.key.windowID,
          sdlEvent.motion.x,
          sdlEvent.motion.y,
          getMouseButton(sdlEvent.button.button),
          getButtonState(sdlEvent.button.state),
          sdlEvent.button.clicks);
    }
    case SDL_MOUSEWHEEL: {
      return MakeUnique<InputEvent<MouseWheelData>>(InputEventType::MouseWheelEvent,
          Core::TimePoint(Core::SteadyClock::now()),
          sdlEvent.key.windowID,
          sdlEvent.motion.x,
          sdlEvent.motion.y);
    }
    default: {
      // eventually handle other type
      CORE_ERROR("InputEvent", "This event type is not handled! SDL: " + std::to_string(sdlEvent.type));
      return nullptr;
    }
    }
  }
}// namespace Input
}// namespace Application