#include "transitions.hpp"
#include "scenemanager.hpp"
#include "scenes.hpp"
#include "sprite.hpp"
#include "space.hpp"
#include "spacemanager.hpp"
#include "transition_fade.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      object_management::objectptr add_transition(transition_list t, int length_ms)
      {
        switch(t)
        {
          case transition_list::fade_in:
            return build_transition_fadein(length_ms);
          case transition_list::fade_out:
            return build_transition_fadeout(length_ms);
          default:
            return {};
        }
      }
    }
  }
}