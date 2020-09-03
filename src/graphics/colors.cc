#include <unordered_map>

#include "colors.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace colors
    {
      static std::unordered_map<color_name, rgb_value> color_data = 
      {
        {color_name::blue, rgb_value(0.f, 0.f, 1.f)},
        {color_name::green, rgb_value(0.f, 1.f, 0.f)},
        {color_name::red, rgb_value(1.f, 0.f, 0.f)},
        {color_name::coral, rgb_value(1.f, 0.5f, 0.31f)},
      };
      
      glm::vec3 get_color(color_name c)
      {
        if(color_data.count(c))
        {
          return color_data.at(c);
        }
        return rgb_value(0.f,0.f,0.f);
      }
    }
  }
}