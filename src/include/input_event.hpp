
#ifndef _WE_INPUT_EVENT_HPP_
#define _WE_INPUT_EVENT_HPP_

#include <events.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace input
  {
    enum class keys
    {
      ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, BACKTICK,
      ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO,
      MINUS, EQUALS, BACKSPACE, TAB,
      Q, W, E, R, T, Y, U, I, O, P, LBRACKET, RBRACKET, BACKSLASH,
      CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
      LSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, FORWARDSLASH, RSHIFT,
      LCTRL, FN, WIN, LALT, SPACE, RALT, CONTEXT, RCTRL,
      INSERT, HOME, PGUP, PGDN, DEL, END, UP, LEFT, RIGHT, DOWN,
      // special
      NONE = -1,
    };

    enum class input_type
    {
      PRESS,
      RELEASE,

      // special
      NONE = -1,
    };

    class input_event : public we::events::event
    {
    public:
      EVENT_NAME(input_event);
      input_event();
      input_event(keys key, input_type type);
      ~input_event();

      keys key;
      input_type type;
    };
  }
}

#endif // !_WE_INPUT_EVENT_HPP_