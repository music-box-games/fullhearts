#ifndef _W_GRAPHICS_HPP_
#define _W_GRAPHICS_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace opengl
    {
      void init();
      void clear();
      void render();
      void shutdown();

      GLFWwindow * get_window();
      ::waifuengine::graphics::shaders::shader& shader_id();
    }

    void init();
    void clear();
    void render();
    void shutdown();
  }
}

#endif // !_W_GRAPHICS_HPP_