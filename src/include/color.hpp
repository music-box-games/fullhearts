#ifndef _WE_COLOR_HPP_
#define _WE_COLOR_HPP_

#ifdef WE_GRAPHICS_SDL2
#include <SDL.h>
#endif // WE_GRAPHICS_SDL2

namespace waifuengine
{
  namespace graphics
  {
    enum class colors
    {
      red,
      blue,
      green,
      black,
    };

    struct color_vals
    {
      unsigned r;
      unsigned g;
      unsigned b;
      unsigned a;
    };

    color_vals get_color(colors c);

    #ifdef WE_GRAPHICS_SDL2
    using color_type = SDL_Color;
    #endif // WE_GRAPHICS_SDL2

    color_type convert_color(colors c);
  }
}

#endif