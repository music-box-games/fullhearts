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
        static_cast<float>(pos.x) / static_cast<float>(window->width()),
        static_cast<float>(pos.y) / static_cast<float>(window->height())
      };

      return vec;
    }

    glm::vec2 screen_coords_to_world_space(glm::vec2 pos)
    {
      auto window = we::graphics::get_current_window();
      glm::vec2 vec {
        static_cast<float>(window->width()) / static_cast<float>(pos.x),
        static_cast<float>(windows->height()) / static_cast<float>(pos.y)
      };
      return vec;
    }
  }
}