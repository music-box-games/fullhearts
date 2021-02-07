#ifndef _WE_BOUNDING_BOX_HPP_
#define _WE_BOUNDING_BOX_HPP_

#include <glm/glm.hpp>
#include "rectangle.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class bounding_box
    {
    public:
      bounding_box(glm::vec2 d);
      bounding_box(int width, int height);
      ~bounding_box();

      bool check_point(glm::vec2 p) const;
      void draw_debug(colors::color c, graphics::transform const& parent_transform);
      void set_dimensions(int width, int height);
      glm::vec2 get_dimensions() const;
      void set_position(glm::vec2 p);
      glm::vec2 get_position() const; 

      rectangle& data();
      rectangle const& data() const;

    private:
      rectangle box;
    };
  }
}

#endif