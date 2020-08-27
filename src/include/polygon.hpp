#ifndef _WE_POLYGON_HPP_
#define _WE_POLYGON_HPP_

#include <vector>
#include <initializer_list>

#include "colors.hpp"
#include "line2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class polygon
    {
    private:
      std::vector<line2d> sides;
    public:
      polygon(std::initializer_list<line2d> lines);
      ~polygon();

      void draw(colors::rgba_value);
    };
  }
}

#endif