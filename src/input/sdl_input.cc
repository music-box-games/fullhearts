#include <sdl_input.hpp>

#ifndef WE_GRAPHICS_SDL2

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
      else if(e.type == SDL_KEYDOWN)
      {
        switch(e.key.keysym.sym)
        {
          
        }
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