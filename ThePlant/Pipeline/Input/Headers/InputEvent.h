#pragma once

#include <variant>

#include "InputDefs.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application {
namespace Input {
  struct EventMetaData
  {
    Core::TimePoint timestamp;
    uint windowId;

    inline EventMetaData(Core::TimePoint timestamp, uint windowId)
      : timestamp(timestamp)
      , windowId(windowId)
    {}
  };

  // Mouse Event data
  struct MouseMetaData : EventMetaData
  {
    int mouseX;
    int mouseY;

    inline MouseMetaData(Core::TimePoint timestamp, uint windowId, int mouseX, int mouseY)
      : EventMetaData(timestamp, windowId)
      , mouseX(mouseX)
      , mouseY(mouseY)
    {}
  };

  struct MouseClickedData : MouseMetaData
  {
    MouseButton button;
    ButtonState state;
    uint clicks;

    inline MouseClickedData(Core::TimePoint timestamp, uint windowId, int mouseX, int mouseY, MouseButton button, ButtonState state, uint clicks)
      : MouseMetaData(timestamp, windowId, mouseX, mouseY)
      , button(button)
      , state(state)
      , clicks(clicks)
    {}
  };

  struct MouseMovedData : MouseMetaData
  {
    int deltaX;
    int deltaY;

    inline MouseMovedData(Core::TimePoint timestamp, uint windowId, int mouseX, int mouseY, int deltaX, int deltaY)
      : MouseMetaData(timestamp, windowId, mouseX, mouseY)
      , deltaX(deltaX)
      , deltaY(deltaY)
    {}
  };

  // for MouseWheelData, mouseX and mouseY become the mouse wheel directions
  struct MouseWheelData : MouseMetaData
  {
    inline MouseWheelData(Core::TimePoint timestamp, uint windowId, int wheelX, int wheelY)
      : MouseMetaData(timestamp, windowId, wheelX, wheelY)
    {}
  };

  // Keyboard Event Data
  struct KeyboardButtonData : EventMetaData
  {
    KeyboardButton button;
    ButtonState state;

    inline KeyboardButtonData(Core::TimePoint timestamp, uint windowId, KeyboardButton button, ButtonState state)
      : EventMetaData(timestamp, windowId)
      , button(button)
      , state(state)
    {}
  };

  using InputEventVariant = std::variant<EventMetaData, MouseClickedData, MouseMovedData, MouseWheelData, KeyboardButtonData>;
  struct InputEvent
  {
    InputEventType inputEventType;
    InputEventVariant inputEventData;
  };

  InputEvent CreateInputEvent(const SDL_Event& sdlEvent);
}// namespace Input
}// namespace Application