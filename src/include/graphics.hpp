#ifndef _W_GRAPHICS_HPP_
#define _W_GRAPHICS_HPP_

#include <GLFW/glfw3.h>

namespace waifuengine
{
  namespace graphics
  {
    namespace opengl
    {
      void init();
      void update(float dt);
      void draw();
      void shutdown();

      GLFWwindow * get_window();
    }
  }
}

#endif // !_W_GRAPHICS_HPP_