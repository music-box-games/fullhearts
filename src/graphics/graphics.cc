#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics.hpp>
#include <window.hpp>
#include <debug.hpp>
#include "notify.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  void init(std::string title)
  {
    // init glfw
    if(!glfwInit())
    {
      // TODO error handling
    }
    // create initial window
    auto w = create_window(title);
    if(!bool(w))
    {
      // TODO error
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Failed to create window!");
    }
    glfwMakeContextCurrent(w.get()->get()); // set the created window to the active window
    
    // init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      // TODO error and shutdown
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Fail to init GLAD!");
    }
    // load shaders
    we::graphics::shaders::load_shaders();
  }

  void shutdown()
  {
    close_all_windows();
    glfwTerminate();
  }

  void clear()
  {
    window::clear_all();
  }

  void present()
  {
    window::present_all();
  }
}
}