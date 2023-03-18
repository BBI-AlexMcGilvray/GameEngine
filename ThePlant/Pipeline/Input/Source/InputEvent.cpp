#include "Pipeline/Input/Headers/InputEvent.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Input {  
  InputEvent CreateInputEvent(const SDL_Event& sdlEvent)
  {
    SCOPED_MEMORY_CATEGORY("Input");
    /*
    Should we be using 'now', or should we be using sdlEvent.key.timestamp?
    */
    switch (sdlEvent.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP: {
      return 
          {
            InputEventType::KeyboardEvent,
            KeyboardButtonData(Core::TimePoint(Core::SteadyClock::now()),
              sdlEvent.key.windowID,
              getKeyboardButton(sdlEvent.key.keysym.sym),
              getButtonState(sdlEvent.key.state))
          };
    }
    case SDL_MOUSEMOTION: {
      return 
        {
          InputEventType::MouseMovedEvent,
          MouseMovedData(Core::TimePoint(Core::SteadyClock::now()),
            sdlEvent.key.windowID,
            sdlEvent.motion.x,
            sdlEvent.motion.y,
            sdlEvent.motion.xrel,
            sdlEvent.motion.yrel)
        };
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP: {
      return 
        {
          InputEventType::MouseClickedEvent,
          MouseClickedData(Core::TimePoint(Core::SteadyClock::now()),
            sdlEvent.key.windowID,
            sdlEvent.motion.x,
            sdlEvent.motion.y,
            getMouseButton(sdlEvent.button.button),
            getButtonState(sdlEvent.button.state),
            sdlEvent.button.clicks)
        };
    }
    case SDL_MOUSEWHEEL: {
      return 
        {
          InputEventType::MouseWheelEvent,
          MouseWheelData(Core::TimePoint(Core::SteadyClock::now()),
            sdlEvent.key.windowID,
            sdlEvent.motion.x,
            sdlEvent.motion.y)
        };
    }
    default: {
      // eventually handle other types
      CORE_ERROR("InputEvent", "This event type is not handled! SDL: " + std::to_string(sdlEvent.type));
      return 
        {
          InputEventType::Undetermined,
          EventMetaData(Core::TimePoint(Core::SteadyClock::now()),
            sdlEvent.key.windowID)
        };
    }
    }
  }
}// namespace Input
}// namespace Application