#include "bounding_box.hpp"

namespace waifuengine
{
  namespace graphics
  {
    bounding_box::bounding_box(int width, int height) : box(rectangle(width, height)) 
    {
      box.set_fill_color(colors::color(0,0,0,255));
    }

    bounding_box::bounding_box(glm::vec2 d) : box(rectangle(d.x, d.y))
    {
      box.set_fill_color(colors::color(0,0,0,255));
    }

    bounding_box::~bounding_box() {}

    bool bounding_box::check_point(glm::vec2 p) const
    {
      // remember that in SFML (0,0) is the top left of the window
      sf::FloatRect r = box.data().getGlobalBounds();
      // left bound
      if(p.x < r.left)
      {
        return false;
      }
      else if(p.x > (r.left + r.width))
      {
        return false;
      }
      else if(p.y < r.top)
      {
        return false;
      }
      else if(p.y > (r.top + r.height))
      {
        return false;
      }
      else
      {
        return true;
      }
    }

    void bounding_box::draw_debug(colors::color c, graphics::transform const& parent_transform)
    {
      box.set_outline_color(c);
      box.draw(parent_transform);
    }

    void bounding_box::set_dimensions(int width, int height)
    {
      box.set_dimensions(width, height);
    }

    glm::vec2 bounding_box::get_dimensions() const
    {
      return box.get_dimensions();
    }

    void bounding_box::set_position(glm::vec2 p)
    {
      box.set_position(p.x, p.y);
    }

    glm::vec2 bounding_box::get_position() const
    {
      return box.get_position();
    }

    rectangle& bounding_box::data()
    {
      return box;
    }

    rectangle const& bounding_box::data() const
    {
      return box;
    }
  }
}