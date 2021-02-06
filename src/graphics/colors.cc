#include "colors.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace colors
    {
      sf::Color convert_we_color_to_sfml_color(color c)
      {
        return sf::Color(c.r, c.g, c.b, c.a);
      }

      color convert_sfml_color_to_we_color(sf::Color c)
      {
        return color(c.r, c.g, c.b, c.a);
      }

      color::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) {}
      color::color(rgb_value c) : r(c.r), g(c.g), b(c.b), a(255) {}
      color::color(rgba_value c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
      color::color(sf::Color c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

      color::~color() {}
    }
  }
}