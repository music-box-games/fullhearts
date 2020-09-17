#ifndef _WE_RECT2D_HPP_
#define _WE_RECT2D_HPP_

#include <array>

#include "line2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class rect2d
    {
    private:
      unsigned int VAO;
      unsigned int VBO;
      unsigned int EBO;

      std::array<float, 8> last_verts;

    public:
      std::array<line2d, 4> sides;
      rect2d(line2d a, line2d b, line2d c, line2d d);
      ~rect2d() = default;

      void draw(glm::vec3 color, float alpha);

      bool operator==(rect2d const& rhs) const; // this only compares the sides, not VAO, VBO, EBO

      std::array<float, 8> get_last_verts() const;
    };
  }
}

#endif