#include <input.hpp>
#include <graphics.hpp>

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
}

void init()
{

}

void shutdown()
{

}

} // namespace input
} // namespace waifuengine