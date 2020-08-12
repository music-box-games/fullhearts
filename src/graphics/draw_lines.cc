#include "draw_lines.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    void draw_line(point2d start, point2d end, colors::rgb_value color)
    {
      draw_line(line2d(start, end), color);
    }

    void draw_line(line2d l, colors::rgb_value color)
    {
      l.draw(color);
    }
  }
}