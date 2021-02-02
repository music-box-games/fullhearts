#ifndef _WE_COLORS_HPP_
#define _WE_COLORS_HPP_

#include <cstdint>
#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace colors
    {
      using rgb_value = glm::vec3;
      using rgba_value = glm::vec4;

      class color
      {
      public:
        color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        color(rgb_value c);
        color(rgba_value c);
        color(sf::Color c);

        ~color();

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
      };

      sf::Color convert_we_color_to_sfml_color(color);
      color convert_sfml_color_to_we_color(sf::Color);
    }
  }
}

#endif