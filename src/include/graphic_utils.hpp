#ifndef _WE_GRAPHIC_UTILS_HPP_
#define _WE_GRAPHIC_UTILS_HPP_

#include <glm/glm.hpp>

namespace waifuengine
{
  namespace utils
  {
    glm::vec2 world_space_to_screen_coords(glm::vec3 pos);
  }
}

#endif