/******************************************************************************/
/*!
\file   sdl_graphics.cc
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Graphics implementation using the SDL2 library.

*/
/******************************************************************************/


#ifdef WE_GRAPHICS_SDL2

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
  static SDL_Renderer * renderer = nullptr;

  void init()
  {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not initialize SDL!");
      std::exit(-1);
    }

    // init other image loading
    int flags = IMG_INIT_PNG;
    if(!(IMG_Init(flags) & flags))
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not init PNG loading!");
      std::exit(-1);
    }

    // init fonts
    if(TTF_Init() == -1)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not init TTF!");
      std::exit(-1);
    }
  }

  void clear()
  {
    SDL_RenderClear(we::graphics::get_window()->data()->get_renderer());
  }

  void render()
  {
    SDL_RenderPresent(we::graphics::get_window()->data()->get_renderer());
  }

  void shutdown()
  {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
  }
}
}
}

#endif // WE_GRAPHICS_SDL2