#ifndef _WE_DRAW_RECTS_HPP_
#define _WE_DRAW_RECTS_HPP_

#include "rect2d.hpp"
#include "colors.hpp"

namespace waifuengine
{
  namespace graphics
  {
    void draw_rect2d(rect2d r, colors::rgb_value, float alpha);
  }
}

#endif