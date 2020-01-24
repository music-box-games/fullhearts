/******************************************************************************/
/*!
\file   window.cc
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  window wrapper class

*/
/******************************************************************************/

#include <window.hpp>

namespace waifuengine
{
namespace graphics
{
namespace opengl
{
  #ifdef WE_GRAPHICS_OPENGL
  window_handle::window_handle()
  {

  }

  window_handle::~window_handle()
  {

  }

  window_handle::data_type * window_handle::data()
  {
    return window;
  }

  void window_handle::clear()
  {

  }

  void window_handle::render()
  {

  }
  #endif // WE_GRAPHICS_OPENGL
}
namespace sdl2
{
  #ifdef WE_GRAPHICS_SDL2
  window_handle::window_handle()
  {

  }

  window_handle::~window_handle()
  {

  }

  window_handle::data_type * window_handle::data()
  {
    return window;
  }

  void window_handle::clear()
  {

  }

  void window_handle::render()
  {

  }
  #endif // WE_GRAPHICS_SDL2
}
}
}