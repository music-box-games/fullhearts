/******************************************************************************/
/*!
\file   sdl_graphics.hpp
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Graphics interface using the SDL2 library.

*/
/******************************************************************************/

#ifndef _WE_SDL_GRAPHICS_HPP_
#define _WE_SDL_GRAPHICS_HPP_
#ifndef WE_GRAPHICS_SDL2

namespace waifuengine
{
  namespace graphics
  {
    namespace sdl2
    {
      void init();
      void clear();
      void render();
      void shutdown();
    }
  }
}

#endif // WE_GRAPHICS_SDL2
#endif // _WE_SDL_GRAPHICS_HPP_