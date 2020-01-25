#include <sdl_input.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <SDL.h>

#include <engine.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace input
{
namespace sdl2
{
  void init()
  {

  }

  void update()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        we::core::engine::shutdown();
      }
    }
  }

  void shutdown()
  {

  }
}
}
}

#endif