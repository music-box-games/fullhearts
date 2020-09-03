
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

      // openGL types
      else if (type == "GLenum")
      {
        ss << va_arg(l, GLenum);
      }
      else if (type == "GLint")
      {
        ss << va_arg(l, GLint);
      }
      else if(type == "GLuint")
      {
        ss << va_arg(l, GLuint);
      }
      else if (type == "GLsizei")
      {
        ss << va_arg(l, GLsizei);
      }
      else if(type == "GLboolean")
      {
        ss << va_arg(l, GLboolean);
      }
      else if(type == "GLbyte")
      {
        ss << va_arg(l, GLbyte);
      }
      else if(type == "GLubyte")
      {
        ss << va_arg(l, GLubyte);
      }
      else if(type == "GLshort")
      {
        ss << va_arg(l, GLshort);
      }
      else if(type == "GLushort")
      {
        ss << va_arg(l, GLushort);
      }
      else if(type == "GLfixed")
      {
        ss << va_arg(l, GLfixed);
      }
      else if (type == "GLint64")
      {
        ss << va_arg(l, GLint64);
      }
      else if(type == "GLuint64")
      {
        ss << va_arg(l, GLuint64);
      }
      else if(type == "GLintptr")
      {
        ss << va_arg(l, GLintptr);
      }
      else if(type == "GLsizeiptr")
      {
        ss << va_arg(l, GLsizeiptr);
      }
      else if(type == "GLsync")
      {
        ss << va_arg(l, GLsync);
      }
      else if(type == "GLbitfield")
      {
        ss << va_arg(l, GLbitfield);
      }
      else if(type == "GLhalf")
      {
        ss << va_arg(l, GLhalf);
      }
      else if(type == "GLfloat")
      {
        ss << va_arg(l, GLfloat);
      }
      else if(type == "GLclampf")
      {
        ss << va_arg(l, GLclampf);
      }
      else if(type == "GLdouble")
      {
        ss << va_arg(l, GLdouble);
      }
      else if(type == "GLclampd")
      {
        ss << va_arg(l, GLclampd);
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