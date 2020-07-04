#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics.hpp>
#include <window.hpp>
#include <debug.hpp>
#include "notify.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  static void release_graphics_assets()
  {
    textures::release_textures();
    textures::release_images();
    shaders::release_shaders();
  }

  void init(std::string title)
  {
    glfwSetErrorCallback(log::_impl::glfw_error_cb);
    // init glfw
    if(!glfwInit())
    {
      // TODO error handling
      log::LOGERROR("Could not init GLFW!");
    }
    // create initial window
    auto w = create_window(title);
    if(!bool(w))
    {
      // TODO error
      log::LOGERROR("Failed to create window!");
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Failed to create window!");
    }
    glfwMakeContextCurrent(w.get()->get()); // set the created window to the active window
    
    // init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      // TODO error and shutdown
      log::LOGERROR("Failed to init GLAD!");
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Failed to init GLAD!");
    }
    // load shaders
    we::graphics::shaders::load_shaders();
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void shutdown()
  {
    // release shaders, textures, and images
    release_graphics_assets();
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