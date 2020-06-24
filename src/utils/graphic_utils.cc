#include "graphic_utils.hpp"
#include "graphics.hpp"
#include "window.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    // just take position as a fraction of 100%
    glm::vec2 world_space_to_screen_coords(glm::vec3 pos)
    {
      auto window = we::graphics::get_current_window();
      glm::vec2 vec { 
        static_cast<float>(pos[0]) / static_cast<float>(window->get_width()),
        static_cast<float>(pos[1]) / static_cast<float>(window->get_height())
      };

      return vec;
    }

    glm::vec2 screen_coords_to_world_space(glm::vec2 pos)
    {
      auto window = we::graphics::get_current_window();
      glm::vec2 vec {
        static_cast<float>(window->get_width()) / static_cast<float>(pos[0]),
        static_cast<float>(window->get_height()) / static_cast<float>(pos[1])
      };
      return vec;
    }
  }
}