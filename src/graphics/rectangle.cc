#include "rectangle.hpp"
#include "graphics.hpp"

namespace waifuengine
{
  namespace graphics
  {
    rectangle::rectangle() : shape<4>(), rect_(sf::RectangleShape(sf::Vector2f(0,0)))
    {
      // get window dimensions
      auto win = get_main_window().lock();
      auto sz = win->data().lock()->getSize();
      set_dimensions(sz.x, sz.y);
    }

    rectangle::rectangle(int w, int h) : shape<4>(), rect_(sf::RectangleShape(sf::Vector2f(w, h))) {}
    rectangle::~rectangle() {}

    void rectangle::draw(transform const& parent_transform) const
    {
      graphics::get_main_window().lock()->data().lock()->draw(rect_, sf::RenderStates(parent_transform.data().getTransform()));
    }

    void rectangle::set_position(float x, float y)
    {
      rect_.setPosition(x, y);
    }

    glm::vec2 rectangle::get_position() const
    {
      auto v = rect_.getPosition();
      return glm::vec2(v.x, v.y);
    }

    void rectangle::set_scale(float x, float y)
    {
      rect_.setScale(x, y);
    }

    glm::vec2 rectangle::get_scale() const
    {
      auto v = rect_.getScale();
      return glm::vec2(v.x, v.y);
    }

    void rectangle::set_rotation(float r)
    {
      rect_.setRotation(r);
    }

    float rectangle::get_rotation() const
    {
      return rect_.getRotation();
    }

    void rectangle::set_dimensions(int width, int height)
    {
      rect_.setSize(sf::Vector2f(width, height));
    }

    glm::vec2 rectangle::get_dimensions() const
    {
      auto v = rect_.getSize();
      return glm::vec2(v.x, v.y);
    }

    void rectangle::set_fill_color(colors::color c)
    {
      rect_.setFillColor(colors::convert_we_color_to_sfml_color(c));
    }

    colors::color rectangle::get_fill_color() const
    {
      return colors::convert_sfml_color_to_we_color(rect_.getFillColor());
    }

    void rectangle::set_outline_color(colors::color c)
    {
      rect_.setOutlineColor(colors::convert_we_color_to_sfml_color(c));
    }

    colors::color rectangle::get_outline_color() const
    {
      return colors::convert_sfml_color_to_we_color(rect_.getOutlineColor());
    }

    void rectangle::set_outline_thickness(float t)
    {
      rect_.setOutlineThickness(t);
    }

    float rectangle::get_outline_thickness() const
    {
      return rect_.getOutlineThickness();
    }

    void rectangle::set_origin(glm::vec2 o)
    {
      rect_.setOrigin(sf::Vector2f(o.x, o.y));
    }

    glm::vec2 rectangle::get_origin() const
    {
      auto v = rect_.getOrigin();
      return glm::vec2(v.x, v.y);
    }

    sf::RectangleShape& rectangle::data()
    {
      return rect_;
    }

    sf::RectangleShape const& rectangle::data() const
    {
      return rect_;
    }
  }
}