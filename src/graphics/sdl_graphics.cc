/******************************************************************************/
/*!
\file   sdl_graphics.cc
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Graphics implementation using the SDL2 library.

*/
/******************************************************************************/

#include <SDL.h>

#ifdef WE_GRAPHICS_SDL2

#include <sdl_graphics.hpp>
#include <utils.hpp>
#include <window.hpp>
#include <graphics.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  void init()
  {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not initialize SDL!");
      std::exit(-1);
    }
  }

  void clear()
  {
    auto * window = we::graphics::get_window()->data()->data();
    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0xF5, 0x42, 0xE3));
    SDL_UpdateWindowSurface(window);
  }

  void render()
  {

  }

  void shutdown()
  {
    SDL_Quit();
  }
}
}
}

#endif // WE_GRAPHICS_SDL2