#ifndef _WE_INPUT_EVENT_HPP_
#define _WE_INPUT_EVENT_HPP_

#include <SFML/Graphics.hpp>

#include "events.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace input
    {
      enum class keys
      {
        unknown,
        esc, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, del,
        backtick, one, two, three, four, five, six, seven, eight, nine, zero, minus, equals, backspace,
        tab, q, w, e, r, t, y, u, i, o, p, bracket_open, bracket_close, backslash,
        capslk, a, s, d, f, g, h, j, k, l, semicolon, single_quote, enter,
        lshift, z, x, c, v, b, n, m, comma, period, forwardslash, rshift,
        lctrl, fn, win, lalt, space, ralt, context, rctrl,
        num_one, num_two, num_three, num_four, num_five, num_six, num_seven, num_eigth, num_nine, num_zero, numlk, num_period,
        num_divide, num_multiply, num_minus, num_plus,
        arrow_up, arrow_left, arrow_down, arrow_right,
      };

      keys from_api_key(sf::Keyboard::Key k);

      enum class actions
      {
        press, release, mouse_button
      };

      class input_event : public events::event
      {
      public:
        EVENT_NAME(input_event);

        input_event(keys k, actions a);
        virtual ~input_event();

        keys key;
        actions action;
      };
    }
  }
}

#endif