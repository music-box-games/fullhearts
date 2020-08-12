#include "draw_rects.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    void draw_rect2d(rect2d r, colors::rgb_value color, float alpha)
    {
      r.draw(color, alpha);
    }
  }
}