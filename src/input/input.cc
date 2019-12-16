#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include <input.hpp>
#include <graphics.hpp>

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
    glfwSetInputMode(we::graphics::opengl::get_window(), GLFW_STICKY_KEYS, GL_TRUE);
  }

  void shutdown()
  {

  }

  void update()
  {
    auto * window = we::graphics::opengl::get_window();
  }
}

void init()
{

}

void shutdown()
{

}

} // namespace input
} // namespace waifuengine