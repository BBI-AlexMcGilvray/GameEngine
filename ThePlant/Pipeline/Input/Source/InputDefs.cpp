#include "Pipeline\Input\Headers\InputDefs.h"

namespace Application {
namespace Input {
  ButtonState GetButtonState(uint sdlState)
  {
    switch (sdlState) {
    case SDL_KEYUP: {
      return ButtonState::Up;
    }
    case SDL_KEYDOWN: {
      return ButtonState::Down;
    }

    default:
      return ButtonState::Undetermined;
    }
  }

  MouseButton GetMouseButton(uint sdlMouseButton)
  {
    switch (sdlMouseButton) {
    case SDL_BUTTON_LEFT: {
      return MouseButton::Left;
    }
    case SDL_BUTTON_MIDDLE: {
      return MouseButton::Middle;
    }
    case SDL_BUTTON_RIGHT: {
      return MouseButton::Right;
    }
    case SDL_BUTTON_X1: {
      return MouseButton::SideOne;
    }
    case SDL_BUTTON_X2: {
      return MouseButton::SideTwo;
    }

    default:
      return MouseButton::Undetermined;
    }
  }

  KeyboardButton GetKeyboardButton(SDL_Keycode sdlKeyCode)
  {
    switch (sdlKeyCode) {
    case SDLK_0: {
      return KeyboardButton::Button_0;
    }
    case SDLK_1: {
      return KeyboardButton::Button_1;
    }
    case SDLK_2: {
      return KeyboardButton::Button_2;
    }
    case SDLK_3: {
      return KeyboardButton::Button_3;
    }
    case SDLK_4: {
      return KeyboardButton::Button_4;
    }
    case SDLK_5: {
      return KeyboardButton::Button_5;
    }
    case SDLK_6: {
      return KeyboardButton::Button_6;
    }
    case SDLK_7: {
      return KeyboardButton::Button_7;
    }
    case SDLK_8: {
      return KeyboardButton::Button_8;
    }
    case SDLK_9: {
      return KeyboardButton::Button_9;
    }

    case SDLK_a: {
      return KeyboardButton::Button_A;
    }
    case SDLK_b: {
      return KeyboardButton::Button_B;
    }
    case SDLK_c: {
      return KeyboardButton::Button_C;
    }
    case SDLK_d: {
      return KeyboardButton::Button_D;
    }
    case SDLK_e: {
      return KeyboardButton::Button_E;
    }
    case SDLK_f: {
      return KeyboardButton::Button_F;
    }
    case SDLK_g: {
      return KeyboardButton::Button_G;
    }
    case SDLK_h: {
      return KeyboardButton::Button_H;
    }
    case SDLK_i: {
      return KeyboardButton::Button_I;
    }
    case SDLK_j: {
      return KeyboardButton::Button_J;
    }
    case SDLK_k: {
      return KeyboardButton::Button_K;
    }
    case SDLK_l: {
      return KeyboardButton::Button_L;
    }
    case SDLK_m: {
      return KeyboardButton::Button_M;
    }
    case SDLK_n: {
      return KeyboardButton::Button_N;
    }
    case SDLK_o: {
      return KeyboardButton::Button_O;
    }
    case SDLK_p: {
      return KeyboardButton::Button_P;
    }
    case SDLK_q: {
      return KeyboardButton::Button_Q;
    }
    case SDLK_r: {
      return KeyboardButton::Button_R;
    }
    case SDLK_s: {
      return KeyboardButton::Button_S;
    }
    case SDLK_t: {
      return KeyboardButton::Button_T;
    }
    case SDLK_u: {
      return KeyboardButton::Button_U;
    }
    case SDLK_v: {
      return KeyboardButton::Button_V;
    }
    case SDLK_w: {
      return KeyboardButton::Button_W;
    }
    case SDLK_x: {
      return KeyboardButton::Button_X;
    }
    case SDLK_y: {
      return KeyboardButton::Button_Y;
    }
    case SDLK_z: {
      return KeyboardButton::Button_Z;
    }

    case SDLK_F1: {
      return KeyboardButton::Button_F1;
    }
    case SDLK_F2: {
      return KeyboardButton::Button_F2;
    }
    case SDLK_F3: {
      return KeyboardButton::Button_F3;
    }
    case SDLK_F4: {
      return KeyboardButton::Button_F4;
    }
    case SDLK_F5: {
      return KeyboardButton::Button_F5;
    }
    case SDLK_F6: {
      return KeyboardButton::Button_F6;
    }
    case SDLK_F7: {
      return KeyboardButton::Button_F7;
    }
    case SDLK_F8: {
      return KeyboardButton::Button_F8;
    }
    case SDLK_F9: {
      return KeyboardButton::Button_F9;
    }
    case SDLK_F10: {
      return KeyboardButton::Button_F10;
    }
    case SDLK_F11: {
      return KeyboardButton::Button_F11;
    }
    case SDLK_F12: {
      return KeyboardButton::Button_F12;
    }
    case SDLK_F13: {
      return KeyboardButton::Button_F13;
    }
    case SDLK_F14: {
      return KeyboardButton::Button_F14;
    }
    case SDLK_F15: {
      return KeyboardButton::Button_F15;
    }
    case SDLK_F16: {
      return KeyboardButton::Button_F16;
    }
    case SDLK_F17: {
      return KeyboardButton::Button_F17;
    }
    case SDLK_F18: {
      return KeyboardButton::Button_F18;
    }
    case SDLK_F19: {
      return KeyboardButton::Button_F19;
    }
    case SDLK_F20: {
      return KeyboardButton::Button_F20;
    }

    case SDLK_AMPERSAND: {
      return KeyboardButton::Button_Ampersand;
    }
    case SDLK_ASTERISK: {
      return KeyboardButton::Button_Asterisk;
    }
    case SDLK_AT: {
      return KeyboardButton::Button_At;
    }
    case SDLK_KP_LEFTBRACE: {
      return KeyboardButton::Button_Brace_Left;
    }
    case SDLK_KP_RIGHTBRACE: {
      return KeyboardButton::Button_Brace_Right;
    }
    case SDLK_LEFTBRACKET: {
      return KeyboardButton::Button_Bracket_Left;
    }
    case SDLK_RIGHTBRACKET: {
      return KeyboardButton::Button_Bracket_Right;
    }
    case SDLK_CARET: {
      return KeyboardButton::Button_Caret;
    }
    case SDLK_COLON: {
      return KeyboardButton::Button_Colon;
    }
    case SDLK_COMMA: {
      return KeyboardButton::Button_Comma;
    }
    case SDLK_DOLLAR: {
      return KeyboardButton::Button_Dollar;
    }
    case SDLK_EQUALS: {
      return KeyboardButton::Button_Equal;
    }
    case SDLK_HASH: {
      return KeyboardButton::Button_Hash;
    }
    case SDLK_EXCLAIM: {
      return KeyboardButton::Button_Exclamation;
    }
    case SDLK_GREATER: {
      return KeyboardButton::Button_Greater;
    }
    case SDLK_LESS: {
      return KeyboardButton::Button_Less;
    }
    case SDLK_MINUS: {
      return KeyboardButton::Button_Minus;
    }
    case SDLK_LEFTPAREN: {
      return KeyboardButton::Button_Parenthesis_Left;
    }
    case SDLK_RIGHTPAREN: {
      return KeyboardButton::Button_Parenthesis_Right;
    }
    case SDLK_PERCENT: {
      return KeyboardButton::Button_Percent;
    }
    case SDLK_PERIOD: {
      return KeyboardButton::Button_Period;
    }
    case SDLK_PLUS: {
      return KeyboardButton::Button_Plus;
    }
    case SDLK_QUESTION: {
      return KeyboardButton::Button_Question;
    }
    case SDLK_QUOTEDBL: {
      return KeyboardButton::Button_Quote_Double;
    }
    case SDLK_QUOTE: {
      return KeyboardButton::Button_Quote_Single;
    }
    case SDLK_SEMICOLON: {
      return KeyboardButton::Button_SemiColon;
    }
    case SDLK_SLASH: {
      return KeyboardButton::Button_Slash;
    }
    case SDLK_BACKSLASH: {
      return KeyboardButton::Button_Slash_Back;
    }
    case SDLK_UNDERSCORE: {
      return KeyboardButton::Button_Underscore;
    }

    case SDLK_LALT: {
      return KeyboardButton::Button_Alt_Left;
    }
    case SDLK_RALT: {
      return KeyboardButton::Button_Alt_Right;
    }
    case SDLK_BACKSPACE: {
      return KeyboardButton::Button_Backspace;
    }
    case SDLK_CAPSLOCK: {
      return KeyboardButton::Button_CapsLock;
    }
    case SDLK_LCTRL: {
      return KeyboardButton::Button_Control_Left;
    }
    case SDLK_RCTRL: {
      return KeyboardButton::Button_Control_Right;
    }
    case SDLK_KP_ENTER: {
      return KeyboardButton::Button_Entry;
    }
    case SDLK_ESCAPE: {
      return KeyboardButton::Button_ESC;
    }
    case SDLK_LSHIFT: {
      return KeyboardButton::Button_Shift_Left;
    }
    case SDLK_RSHIFT: {
      return KeyboardButton::Button_Shift_Right;
    }
    case SDLK_SPACE: {
      return KeyboardButton::Button_Space;
    }
    case SDLK_TAB: {
      return KeyboardButton::Button_Tab;
    }

    default:
      return KeyboardButton::Undetermined;
    }
  }
}// namespace Input
}// namespace Application