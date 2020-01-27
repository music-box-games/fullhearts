#ifndef _WE_SDL_INPUT_HPP_
#define _WE_SDL_INPUT_HPP_


#ifdef WE_GRAPHICS_SDL2
namespace waifuengine
{
  namespace input
  {
    namespace sdl2
    {
      void init();
      void update();
      void shutdown();
    }
  }
}
#endif // WE_GRAPHICS_SDL2

#endif // !_WE_SDL_INPUT_HPP_