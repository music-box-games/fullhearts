#ifndef _WE_COLORS_HPP_
#define _WE_COLORS_HPP_

#include <glm/glm.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace colors
    {
      enum class color_name
      {
        red,
        green,
        blue,
      };

      glm::vec3 get_color(color_name c);

      using rgb_value = glm::vec3;
      using rgba_value = glm::vec4;
    }
  }
}

#endif