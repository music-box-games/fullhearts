#ifndef _WE_TRANSITIONS_HPP_
#define _WE_TRANSISTIONS_HPP_

#include "gameobject.hpp"
#include "transition_fade.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      enum class transition_list
      {
        fade_in,
        fade_out,
      };
      object_management::objectptr add_transition(transition_list t);

    }
  }
}

#endif