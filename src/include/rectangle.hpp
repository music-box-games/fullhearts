#ifndef _WE_RECTANGLE_HPP_
#define _WE_RECTANGLE_HPP_

#include "shape.hpp"
#include "transform.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class rectangle : public shape<4>
    {
    public:
      rectangle();
      rectangle(int width, int height);
      virtual ~rectangle();

      virtual void draw(transform const& parent_transform) const;


      void set_position(float x, float y);
      glm::vec2 get_position() const;
      void set_scale(float x, float y);
      glm::vec2 get_scale() const;
      void set_rotation(float rot);
      float get_rotation() const;

      void set_dimensions(int width, int height);
      glm::vec2 get_dimensions() const;

      void set_fill_color(colors::color c);
      colors::color get_fill_color() const;
      void set_outline_color(colors::color c);
      colors::color get_outline_color() const;
      void set_outline_thickness(float t);
      float get_outline_thickness() const;

      void set_origin(glm::vec2 o);
      glm::vec2 get_origin() const;

      sf::RectangleShape& data();
      sf::RectangleShape const& data() const;

    private:
      friend class core::debug::imgui_listener;
      sf::RectangleShape rect_;
    };
  }
}

#endif