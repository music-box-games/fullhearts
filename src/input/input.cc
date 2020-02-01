/******************************************************************************/
/*!
\file   input.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Handles user input.

*/
/******************************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include <input.hpp>
#include <graphics.hpp>
#include <log.hpp>
#include <engine.hpp>

#ifdef WE_GRAPHICS_SDL2
#include <sdl_input.hpp>
#endif // WE_GRAPHICS_SDL2

namespace we = ::waifuengine;

namespace waifuengine
{
namespace input
{
void init()
{
  #ifdef WE_GRAPHICS_SDL2
  sdl2::init();
  #endif
}

void shutdown()
{
  #ifdef WE_GRAPHICS_SDL2
  sdl2::shutdown();
  #endif
}

void update()
{
  #ifdef WE_GRAPHICS_SDL2
  sdl2::update();
  #endif
}

void get_mouse_position(int * x, int * y)
{
  #ifdef WE_GRAPHICS_SDL2
  sdl2::get_mouse_position(x, y);
  #endif
}

} // namespace input
} // namespace waifuengine
