#ifndef _WE_SHADER_HPP_
#define _WE_SHADER_HPP_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace waifuengine
{
  namespace graphics
  {
    namespace shaders
    {
      namespace opengl
      {
        GLuint load(std::string vert_shader, std::string frag_shader);
      }

      
    }
  }
}

#endif // !_WE_SHADER_HPP_