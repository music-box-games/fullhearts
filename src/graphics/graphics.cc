#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <graphics.hpp>
#include <window.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  void init(std::string title)
  {
    // init glfw
    glewExperimental = true;
    if(!glfwInit())
    {
      // TODO error handling
    }
    // create initial window
    auto w = create_window(title);
    if(!bool(w))
    {
      // TODO error
    }
    glfwMakeContextCurrent(w.get()->get());
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
      // TODO error
    }
  }
}
}