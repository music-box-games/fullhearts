#ifndef _WE_TRANSITION_FADE_HPP_
#define _WE_TRANSITION_FADE_HPP_

#include "gameobject.hpp"
#include "timer_manager.hpp"
#include "timer.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      object_management::objectptr build_transition_fade();

      class fade : public object_management::gameobject
      {
      private:
        void time_up();
      public:
        fade(std::string const& name, int ms);
        ~fade() = default;
      };
    }
  }
}

#endif