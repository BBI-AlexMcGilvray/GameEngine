#pragma once

#include "Dependencies/Includes/sdl.h"

#include "Core/Headers/CoreDefs.h"

using namespace Core;

namespace Application {
namespace Input {
  /*
  Need controller equivalents for these
  */

  enum class InputEventType {
    Undetermined,
    MouseClickedEvent,
    MouseMovedEvent,
    MouseWheelEvent,
    KeyboardEvent
  };

  enum class ButtonState {
    Undetermined,
    Up,
    Down
  };

  ButtonState getButtonState(uint sdlState);

  enum class MouseButton {
    Undetermined,
    Left,
    Middle,
    Right,
    SideOne,
    SideTwo
  };

  MouseButton getMouseButton(uint sdlMouseButton);

  enum class KeyboardButton {
    Undetermined,

    Button_0,
    Button_1,
    Button_2,
    Button_3,
    Button_4,
    Button_5,
    Button_6,
    Button_7,
    Button_8,
    Button_9,

    Button_A,
    Button_B,
    Button_C,
    Button_D,
    Button_E,
    Button_F,
    Button_G,
    Button_H,
    Button_I,
    Button_J,
    Button_K,
    Button_L,
    Button_M,
    Button_N,
    Button_O,
    Button_P,
    Button_Q,
    Button_R,
    Button_S,
    Button_T,
    Button_U,
    Button_V,
    Button_W,
    Button_X,
    Button_Y,
    Button_Z,

    Button_F1,
    Button_F2,
    Button_F3,
    Button_F4,
    Button_F5,
    Button_F6,
    Button_F7,
    Button_F8,
    Button_F9,
    Button_F10,
    Button_F11,
    Button_F12,
    Button_F13,
    Button_F14,
    Button_F15,
    Button_F16,
    Button_F17,
    Button_F18,
    Button_F19,
    Button_F20,

    Button_Ampersand,
    Button_Asterisk,
    Button_At,
    Button_Brace_Left,
    Button_Brace_Right,
    Button_Bracket_Left,
    Button_Bracket_Right,
    Button_Caret,
    Button_Colon,
    Button_Comma,
    Button_Dollar,
    Button_Equal,
    Button_Hash,
    Button_Exclamation,
    Button_Greater,
    Button_Less,
    Button_Minus,
    Button_Parenthesis_Left,
    Button_Parenthesis_Right,
    Button_Percent,
    Button_Period,
    Button_Plus,
    Button_Question,
    Button_Quote_Double,
    Button_Quote_Single,
    Button_SemiColon,
    Button_Slash,
    Button_Slash_Back,
    Button_Underscore,

    Button_Alt_Left,
    Button_Alt_Right,
    Button_Backspace,
    Button_CapsLock,
    Button_Control_Left,
    Button_Control_Right,
    Button_Entry,
    Button_ESC,
    Button_Shift_Left,
    Button_Shift_Right,
    Button_Space,
    Button_Tab
  };

  KeyboardButton getKeyboardButton(SDL_Keycode sdlKeyCode);
}// namespace Input
}// namespace Application