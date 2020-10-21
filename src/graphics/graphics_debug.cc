
#include <unordered_map>
#include "graphics_debug.hpp"

namespace we = waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace graphics_debug
    {
      namespace gl_function_detailed_errors
      {
        detailed_error_funcs::detailed_error_funcs(data_func_type pn, data_func_type pt, detail_func_type ed) : pnames(pn), ptypes(pt), edetails(ed) {}

        static std::unordered_map<std::string, detailed_error_funcs> detailed_funcs =
        {
          {
            "glTexImage2D",
            detailed_error_funcs(
              []() -> std::vector<std::string> { return std::vector<std::string>({"target", "level", "internalformat", "width", "height", "border", "format", "type", "data"}); },
              []() -> std::vector<std::string> { return std::vector<std::string>({"GLenum", "GLint", "GLint", "GLsizei", "GLsizei", "GLint", "GLenum", "GLenum", "const void *"}); }
            )
          },
          {
            "glUniform1i",
            detailed_error_funcs(
              []() -> std::vector<std::string> { return std::vector<std::string>({"location", "v0"}); },
              []() -> std::vector<std::string> { return std::vector<std::string>({"GLint", "GLint"}); }
            )
          },
          {
            "glBindVertexArray",
            detailed_error_funcs(
              []() -> std::vector<std::string> { return std::vector<std::string>({"array"}); },
              []() -> std::vector<std::string> { return std::vector<std::string>({"GLuint"}); },
              []() -> std::string { return "GL_INVALID_OPERATION is generated if array is not zero or the name of a vertex array object previously returned from a call to glGenVertexArrays."; }
            )
          },
          {
            "glCreateShader",
            detailed_error_funcs(
              []() -> std::vector<std::string> { return std::vector<std::string>({"shaderType"}); },
              []() -> std::vector<std::string> { return std::vector<std::string>({"GLenum"}); },
              []() -> std::string { return "This function returns 0 if an error occurs creating the shader object. GL_INVALID_ENUM is generated if shaderType is not an accepted value."; }
            )
          }
        };

        std::vector<std::string> param_names(std::string func_name)
        {
          if(detailed_funcs.count(func_name))
          {
            return detailed_funcs.at(func_name).pnames();
          }
          return {};
        }

        std::vector<std::string> param_types(std::string func_name)
        {
          if(detailed_funcs.count(func_name))
          {
            return detailed_funcs.at(func_name).ptypes();
          }
          return {};
        }

        std::string extra_details(std::string func_name)
        {
          if(detailed_funcs.count(func_name))
          {
            return detailed_funcs.at(func_name).edetails();
          }
          return std::string();
        }

        bool has_detailed_error_info(std::string func_name)
        {
          return detailed_funcs.count(func_name);
        }
      }
    }
  }
}