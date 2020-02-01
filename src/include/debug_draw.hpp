#ifndef _WE_DEBUG_DRAW_HPP_
#define _WE_DEBUG_DRAW_HPP_

namespace waifuengine
{
  namespace graphics
  {
    namespace debug
    {
      void add_debug_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a);

      void draw_debug();
    }
  }
}

#endif