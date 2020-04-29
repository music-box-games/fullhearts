#ifndef _WE_INPUT_HPP_
#define _WE_INPUT_HPP_

#include <events.hpp>
#include <window.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace input
    {
      void process();

      enum class key
      {
        escape,
        default,
      };

      enum class action
      {
        press,
        release,
        default,
      };

      class input_event : public waifuengine::events::event
      {
      public:
        EVENT_NAME(input_event);

        input_event();
        input_event(key, action, window_id_type);
        ~input_event();

        key k;
        action a;
        waifuengine::graphics::window_id_type w;
      };
    }
  }
}

#endif