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

#include <event_manager.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace input
{
namespace opengl
{
  void init()
  {
    we::log::trace("opengl input: init");
  }

  void shutdown()
  {
    we::log::trace("opengl input: shutdown");
  }

  void update()
  {
    we::log::pedantic("opengl input: update");
    auto * window = we::graphics::opengl::get_window();
    if(glfwWindowShouldClose(window))
    {
      we::core::engine::shutdown();
    }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  }
}

void init()
{
  we::log::trace("input: init");
  opengl::init();
}

void shutdown()
{
  opengl::shutdown();
  we::log::trace("input: shutdown");
}

void update()
{
  we::log::pedantic("input: update");
  opengl::update();
}

} // namespace input
} // namespace waifuengine