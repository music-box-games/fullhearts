/******************************************************************************/
/*!
\file   shader.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Shader class handles compiling, using, and accessing shaders.

*/
/******************************************************************************/

#ifndef _WE_SHADER_HPP_
#define _WE_SHADER_HPP_

#include <string>
#include <string_view>
#include <memory>
#include <optional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <component.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace shaders
    {
      class shader : public ::waifuengine::components::component<shader>
      {
      private:
        unsigned int program_id;

      public:
        COMPONENT_NAME(shader);
        COMPONENT_TYPE(shader);

        shader();
        shader(std::string vert_shader, std::string frag_shader);
        shader(shader const& other);
        ~shader();

        virtual void update(float dt) override;
        virtual void draw() const override;

        void use() const;

        unsigned int id() const;

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

      std::optional<std::shared_ptr<shader>> load_shader(std::string vertex_shader, std::string fragment_shader, std::string name);
      std::optional<std::shared_ptr<shader>> get_shader(std::string name);

      void init();
      void shutdown();
    }
  }
}

#endif // !_WE_SHADER_HPP_