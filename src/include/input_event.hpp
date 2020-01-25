#ifndef _WE_INPUT_EVENT_HPP_
#define _WE_INPUT_EVENT_HPP_

#include <events.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace input
  {
    enum class inputs
    {
      BACKTICK,
      ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO,
      MINUS, EQUALS, BACKSPACE, TAB,
      Q, W, E, R, T, Y, Y, U, I, O, P, LBRACKET, RBRACKET, BACKSLASH,
      CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
      LSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, FORWARDSLASH, RSHIFT,
      LCTRL, FN, WIN, LALT, SPACE, RALT, PAGE, RCTRL,
    };

    enum class input_type
    {
      PRESS,
      RELEASE,
    };

    class input_event : public we::events::event
    {
    public:
      EVENT_NAME(input_event);
      input_event();
      input_event(inputs key, input_type type);
      ~input_event();
      inputs key;
      input_type type;
    };
  }
}

#endif // !_WE_INPUT_EVENT_HPP_