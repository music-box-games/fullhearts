#include "colors.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace colors
    {
      glm::vec3 get_color(color_name c)
      {
        switch(c)
        {
          case color_name::blue:
            return glm::vec3{0.f, 0.f, 1.f};
          case color_name::green:
            return glm::vec3(0.f, 1.f, 0.f);
          case color_name::red:
            return glm::vec3(1.f, 0.f, 0.f);
          default:
            return glm::vec3{0.f,0.f,0.f};
        }
      }
    }
  }
}