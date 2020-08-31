
#include "type_utils.hpp"
#include "graphics.hpp"

namespace waifuengine
{
  namespace utils
  {
    void insert_va_arg_into_sstream(std::stringstream & ss, std::string const& type, va_list l)
    {
      if (type == "int")
      {
        ss << va_arg(l, int);
      }
      else if (type == "float")
      {
        ss << va_arg(l, float);
      }
      else if (type == "double")
      {
        ss << va_arg(l, double);
      }
      else if (type == "std::size_t")
      {
        ss << va_arg(l, std::size_t);
      }
      else if (type == "size_t")
      {
        ss << va_arg(l, size_t);
      }

      else if (type == "GLenum")
      {
        ss << va_arg(l, GLenum);
      }
      else if (type == "GLint")
      {
        ss << va_arg(l, GLint);
      }
      else if (type == "GLsizei")
      {
        ss << va_arg(l, GLsizei);
      }
      else if (type == "const void *")
      {
        ss << "0x" << std::hex << va_arg(l, const void *);
      }
      else
      {
      }
    }
  } // namespace utils
} // namespace waifuengine