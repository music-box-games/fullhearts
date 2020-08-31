
#ifndef _WE_GRAPHICS_HPP_
#define _WE_GRAPHICS_HPP_


#define GLAD_DEBUG
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace waifuengine
{
  namespace graphics
  {
    namespace impl
    {
      void opengl_check_error();
    }
    void init(std::string title);
    void shutdown();

    void present();
    void clear();

    std::string opengl_info();
  }
}

#define GL_CHECK() waifuengine::graphics::impl::opengl_check_error()

#endif