#ifndef _WE_BOUNDING_BOX_HPP_
#define _WE_BOUNDING_BOX_HPP_

#include <glm/glm.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class bounding_box
    {
    public:
      bounding_box();
      ~bounding_box();

      bool check_point(glm::vec2 p);

      void draw() const;
    };
  }
}

#endif