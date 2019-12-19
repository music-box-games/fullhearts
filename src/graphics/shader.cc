// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/

#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

#include <shader.hpp>
#include <log.hpp>
#include <utils.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace shaders
    {
      namespace opengl
      {
        GLuint load(std::string vert_shader, std::string frag_shader)
        {
          {
            std::stringstream ss;
            ss << "Loading shaders:\n" << vert_shader << '\n' << frag_shader;
            we::log::trace(ss.str());
          }
          GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
          GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

          std::string vert_src, frag_src;

          // copy vertex and frag shader source code into memory
          auto load_func = [](std::string f, std::string * dest) -> void {
            *dest = we::utils::parse_file_to_string(f);
          };

          std::vector<std::thread> load_threads;
          std::thread t1(load_func, vert_shader, &vert_src);
          std::thread t2(load_func, frag_shader, &frag_src);

          load_threads.push_back(std::move(t1));
          load_threads.push_back(std::move(t2));
          std::for_each(load_threads.begin(), load_threads.end(), [](std::thread& t) {
            t.join();
          });

          GLint result = GL_FALSE;
          int info_log_length;

          // compile vertex shader
          {
            std::stringstream ss;
            ss << "Compiling shader: " << vert_shader << '\n'
            << "shader source:\n" << vert_src;
            we::log::trace(ss.str());
          }
          const char *vert_src_ptr = vert_src.c_str();
          glShaderSource(vert_id, 1, &vert_src_ptr, NULL);
          glCompileShader(vert_id);
          // check vertex shader
          glGetShaderiv(vert_id, GL_COMPILE_STATUS, &result);
          glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &info_log_length);
          if(info_log_length > 0)
          {
            std::vector<char> vert_error_message(info_log_length + 1);
            glGetShaderInfoLog(vert_id, info_log_length, NULL, &vert_error_message[0]);
            std::stringstream ss;
            ss << "Error compiling shader: " << vert_shader << ". " << vert_error_message.data();
            we::log::error(ss.str());
            return 0;
          }

          // compile fragment shader
          {
            std::stringstream ss;
            ss << "compiling shader: " << frag_shader << '\n'
            << "shader source:\n" << frag_src;
            we::log::trace(ss.str());
          }
          const char * frag_src_ptr = frag_src.c_str();
          glShaderSource(frag_id, 1, &frag_src_ptr, NULL);
          glCompileShader(frag_id);
          // check frag shader
          glGetShaderiv(frag_id, GL_COMPILE_STATUS, &result);
          glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &info_log_length);
          if(info_log_length > 0)
          {
            std::vector<char> frag_error_message(info_log_length + 1);
            glGetShaderInfoLog(frag_id, info_log_length, NULL, &frag_error_message[0]);
            std::stringstream ss;
            ss << "Error compiling shader: " << frag_shader << ". " << frag_error_message.data();
            we::log::error(ss.str());
            return 0;
          }

          // link program
          we::log::trace("Linking shader program");
          GLuint program_id = glCreateProgram();
          glAttachShader(program_id, vert_id);
          glAttachShader(program_id, frag_id);
          glLinkProgram(program_id);

          // check linking successful
          glGetProgramiv(program_id, GL_LINK_STATUS, &result);
          glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
          if(info_log_length > 0)
          {
            std::vector<char> prg_error_message(info_log_length + 1);
            glGetProgramInfoLog(program_id, info_log_length, NULL, &prg_error_message[0]);
            std::stringstream ss;
            ss << "Error linking shader program. " << prg_error_message.data();
            we::log::error(ss.str());
            return 0;
          }
          // free memory
          glDeleteShader(vert_id);
          glDeleteShader(frag_id);

          return program_id;
        }
      }

      shader::shader() : program_id(0) {}

      shader::shader(std::string vert_shader, std::string frag_shader)
      {
        program_id = we::graphics::shaders::opengl::load(vert_shader, frag_shader);
      }

      shader::shader(shader const& other)
      {
        program_id = other.program_id;
      }

      shader::~shader()
      {

      }

      void shader::update(float)
      {

      }

      void shader::draw() const
      {
        
      }

      void shader::use() const
      {
        glUseProgram(program_id);
      }
    }
  }
}