#ifndef _WE_GRAPHICS_HPP_
#define _WE_GRAPHICS_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace waifuengine
{
  namespace graphics
  {
    namespace impl
    {
      void check_gl();
    }
    void init(std::string title);
    void shutdown();

    void present();
    void clear();
  }
}

#define GL_CHECK() waifuengine::graphics::impl::check_gl()

#endif