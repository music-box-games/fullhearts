/******************************************************************************/
/*!
\file   shader.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Shader class. Handles creating, compiling, and using shaders.

*/
/******************************************************************************/

#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <unordered_map>

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
          // create ids for vertex and fragment shaders
          GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
          GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

          std::string vert_src, frag_src;

          // copies vertex and frag shader source code into memory
          auto load_func = [](std::string f, std::string * dest) -> void {
            *dest = we::utils::parse_file_to_string(f);
          };

          // TODO: convert to std::jthread when supported
          // load source code in separate threads
          std::vector<std::thread> load_threads;
          std::thread t1(load_func, vert_shader, &vert_src);
          std::thread t2(load_func, frag_shader, &frag_src);

          load_threads.push_back(std::move(t1));
          load_threads.push_back(std::move(t2));
          // wait for jobs to finish
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
          glShaderSource(vert_id, 1, &vert_src_ptr, NULL); // pass source to opengl
          glCompileShader(vert_id); // run compiler
          // check vertex shader
          glGetShaderiv(vert_id, GL_COMPILE_STATUS, &result); // check compile status
          glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &info_log_length); // check that log is empty
          if(info_log_length > 0)
          {
            // if log isn't empty, report what errors happened
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
          glShaderSource(frag_id, 1, &frag_src_ptr, NULL); // pass source to opengl, assign to frag_id
          glCompileShader(frag_id); // compile
          // check frag shader
          glGetShaderiv(frag_id, GL_COMPILE_STATUS, &result); // check compile
          glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &info_log_length); // check log
          if(info_log_length > 0)
          {
            // report error
            std::vector<char> frag_error_message(info_log_length + 1);
            glGetShaderInfoLog(frag_id, info_log_length, NULL, &frag_error_message[0]);
            std::stringstream ss;
            ss << "Error compiling shader: " << frag_shader << ". " << frag_error_message.data();
            we::log::error(ss.str());
            return 0;
          }

          // link program
          we::log::trace("Linking shader program");
          GLuint program_id = glCreateProgram(); // create shader program
          glAttachShader(program_id, vert_id); // add vertex shader
          glAttachShader(program_id, frag_id); // add fragment shader
          glLinkProgram(program_id); // link program

          // check linking successful
          glGetProgramiv(program_id, GL_LINK_STATUS, &result); // check link
          glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length); // check log
          if(info_log_length > 0)
          {
            // errors
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
        // load, compile, and link shader program from provided source
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

      unsigned int shader::id() const
      {
        return program_id;
      }

      void shader::set_uniform1(std::string uniform_name, int value)
        {
          glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), value);
        }

        void shader::set_uniform1(std::string uniform_name, bool value)
        {
          glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), (int)value);
        }

        void shader::set_uniform1(std::string uniform_name, float value)
        {
          glUniform1f(glGetUniformLocation(program_id, uniform_name.c_str()), value);
        }

        void shader::set_uniform4(std::string uniform_name, int val1, int val2, int val3, int val4)
        {
          glUniform4i(glGetUniformLocation(program_id, uniform_name.c_str()), val1, val2, val3, val4);
        }

        void shader::set_uniform4(std::string uniform_name, bool val1, bool val2, bool val3, bool val4)
        {
          glUniform4i(glGetUniformLocation(program_id, uniform_name.c_str()), (int)val1, (int)val2, (int)val3, (int)val4);
        }

        void shader::set_uniform4(std::string uniform_name, float val1, float val2, float val3, float val4)
        {
          glUniform4f(glGetUniformLocation(program_id, uniform_name.c_str()), val1, val2, val3, val4);
        }

      static std::unordered_map<std::string, unsigned int> shader_names;
      static std::unordered_map<unsigned int, std::shared_ptr<shader>> loaded_shaders;

      std::optional<std::shared_ptr<shader>> load_shader(std::string vertex_shader, std::string fragment_shader, std::string name)
      {
        shader * s = new shader(vertex_shader, fragment_shader);
        if(s == nullptr) return {};
        std::shared_ptr<shader> ptr(s);
        shader_names[name] = s->id();
        loaded_shaders[s->id()] = ptr;
        return std::optional(ptr);
      }

      std::optional<std::shared_ptr<shader>> get_shader(std::string name)
      {
        if(shader_names.count(name))
        {
          return std::optional(loaded_shaders[shader_names[name]]);
        }
        else return {};
      }

      void init() {}
      void shutdown() 
      { 
        shader_names.clear();
        loaded_shaders.clear();
      }
    }
  }
}