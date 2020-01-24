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
#include <log.hpp>

namespace waifuengine
{
namespace graphics
{
namespace opengl
{
  #ifdef WE_GRAPHICS_OPENGL
  window_handle::window_handle()
  {
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // use opengl version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // modern core
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // forward compat for macos
    return glfwCreateWindow(1024, 768, "Full Hearts", NULL, NULL); // TODO make resolution variable
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
    we::log::pedantic("opengl window_handle: clear");
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void window_handle::render()
  {
    we::log::pedantic("opengl window_handle: render");

    glfwPollEvents();
    glfwSwapBuffers(window_);
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

window::window()
{
  handle = std::unique_ptr<window_type>(new window_type());
}

window::~window()
{

}

std::weak_ptr<window::window_type> window::data()
{
  return std::weak_ptr<window_type>(handle);
}

void window::clear()
{
  handle->clear();
}

void window::render()
{
  handle->render()
}

}
}