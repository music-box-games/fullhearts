#include "circle.hpp"
#include "graphics.hpp"

namespace waifuengine
{
  namespace graphics
  {
    circle::circle(int radius) : shape<0>(), cs(sf::CircleShape(radius)), fill_color_(sf::Color::Black), outline_color_(sf::Color::Black) {}

    void circle::draw()
    {
      // TODO: change the way windows be working probably

    }

    void circle::radius(int radius)
    {
      cs.setRadius(radius);
    }

    int circle::radius() const
    {
      return cs.getRadius();
    }

    void circle::fill_color(colors::color c)
    {
      cs.setFillColor(colors::convert_we_color_to_sfml_color(c));
    }

    colors::color circle::fill_color() const
    {
      return colors::convert_sfml_color_to_we_color(cs.getFillColor());
    }

    void circle::outline_color(colors::color c)
    {
      cs.setOutlineColor(colors::convert_we_color_to_sfml_color(c));
    }

    colors::color circle::outline_color() const
    {
      return colors::convert_sfml_color_to_we_color(cs.getOutlineColor());
    }

    void circle::position(glm::vec2 p)
    {
      cs.setPosition(p.x, p.y);
    }

    glm::vec2 circle::position() const
    {
      auto pos = cs.getOrigin();
      return glm::vec2(pos.x, pos.y);
    }
  }
}