#ifndef _WE_DRAW_LINES_HPP_
#define _WE_DRAW_LINES_HPP_

#include "point2d.hpp"
#include "colors.hpp"
#include "line2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    void draw_line(point_2d start, point_2d end, colors::rgb_value color, float alpha);
    void draw_line(line2d l, colors::rgb_value color, float alpha);
  }
}

#endif