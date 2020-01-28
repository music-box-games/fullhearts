#include <sdl_input.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <unordered_map>

#include <SDL.h>
#include <input_event.hpp>
#include <event_manager.hpp>
#include <engine.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace input
{
namespace sdl2
{

  static std::unordered_map<SDL_Keycode, we::input::inputs> keymap = 
  {
    { SDLK_ESCAPE, we::input::inputs::ESCAPE },
  };

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
        case SDLK_ESCAPE:
          we::core::engine::shutdown();
          return;
        default:
          break;
        }
        if(keymap.count(e.key.keysym.sym))
        {
          we::input::input_event ev;
          ev.key = keymap[e.key.keysym.sym];
          ev.type = we::input::input_type::PRESS;
          we::events::handle<input_event>(&ev);
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