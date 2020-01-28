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
#include <utils.hpp>
#include <sdl_graphics.hpp>


namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace opengl
{
  #ifdef WE_GRAPHICS_OPENGL
  window_handle::window_handle(unsigned width, unsigned height, std::string title)
  {
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // use opengl version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // modern core
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // forward compat for macos
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL); // TODO make resolution variable
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
    glfwSwapBuffers(window);
  }
  #endif // WE_GRAPHICS_OPENGL
}
namespace sdl2
{
  #ifdef WE_GRAPHICS_SDL2
  window_handle::window_handle(unsigned width, unsigned height, std::string title) : window(nullptr), renderer(nullptr)
  {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not create SDL Window!");
      std::exit(-1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Could not create SDL renderer");
      std::exit(-1);
    }
    SDL_SetRenderDrawColor(renderer, 0xF5, 0x42, 0xE3, 0xFF);
  }

  window_handle::~window_handle()
  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  window_handle::data_type * window_handle::data()
  {
    return window;
  }

  void window_handle::clear()
  {
    we::graphics::sdl2::clear();
  }

  void window_handle::render()
  {
    we::graphics::sdl2::render();
  }

  SDL_Renderer * window_handle::get_renderer()
  {
    return renderer;
  }

  #endif // WE_GRAPHICS_SDL2
}

window::window(unsigned width, unsigned height, std::string title)
{
  handle = std::shared_ptr<window_type>(new window_type(width, height, title));
}

window::~window()
{

}

std::shared_ptr<window::window_type> window::data()
{
  return handle;
}

void window::clear()
{
  handle->clear();
}

void window::render()
{
  handle->render();
}
}
}
