#ifndef _WE_LINE_2D_HPP_
#define _WE_LINE_2D_HPP_

#include <glm/vec3.hpp>

#include "point2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class line2d
    {
    private:
      unsigned int VBO;
      unsigned int VAO;
      unsigned int EBO;
    public:
      point_2d start;
      point_2d end;

      line2d();
      line2d(point_2d s, point_2d e);
      ~line2d();

      void draw(glm::vec3 color, float alpha);

      bool operator==(line2d const& rhs) const;
    };
  }
}

#endif