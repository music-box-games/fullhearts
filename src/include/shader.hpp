#ifndef _WE_SHADER_HPP_
#define _WE_SHADER_HPP_

#include <string>
#include <string_view>

#include <glad/glad.h>
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

      class shader
      {
      private:
        unsigned int program_id;

      public:
        shader();
        shader(std::string vert_shader, std::string frag_shader);
        shader(shader const& other);
        ~shader();

        void use() const;

        template<typename uniform_type>
        void set_uniform1(std::string, uniform_type);
        template<typename uniform_type>
        void set_uniform4(std::string, uniform_type, uniform_type, uniform_type, uniform_type);

        template<>
        void set_uniform1(std::string uniform_name, int value)
        {
          glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), value);
        }

        template<>
        void set_uniform1(std::string uniform_name, bool value)
        {
          glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), (int)value);
        }

        template<>
        void set_uniform1(std::string uniform_name, float value)
        {
          glUniform1f(glGetUniformLocation(program_id, uniform_name.c_str()), value);
        }

        template<>
        void set_uniform4(std::string uniform_name, int val1, int val2, int val3, int val4)
        {
          glUniform4i(glGetUniformLocation(program_id, uniform_name.c_str()), val1, val2, val3, val4);
        }

        template<>
        void set_uniform4(std::string uniform_name, bool val1, bool val2, bool val3, bool val4)
        {
          glUniform4i(glGetUniformLocation(program_id, uniform_name.c_str()), (int)val1, (int)val2, (int)val3, (int)val4);
        }

        template<>
        void set_uniform4(std::string uniform_name, float val1, float val2, float val3, float val4)
        {
          glUniform4f(glGetUniformLocation(program_id, uniform_name.c_str()), val1, val2, val3, val4);
        }
      };
    }
  }
}

#endif // !_WE_SHADER_HPP_