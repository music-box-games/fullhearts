
#include <sstream>
#include <vector>

#include "graphics.hpp"
#include "window.hpp"
#include "debug.hpp"
#include "notify.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "log.hpp"
#include "utils.hpp"
#include "graphics_debug.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  namespace impl
  {
    void opengl_check_error()
    {
      
    }

    static void glfw_error_callback_func(int error, const char * description)
    {
      std::stringstream ss;
      ss << "[glfw_error_callback_func]: (" << error << ") " << description;
      log::LOGERROR(ss.str());
    }

    static void glad_postcall_callback_func(const char * name, void * func_ptr, int len_args, ...)
    {
      

      std::stringstream buffer;
      std::stringstream message;
      GLenum error = glad_glGetError();
      // break early to avoid constructing all the strings
      if(error == GL_NO_ERROR)
      {
        return;
      }
      std::string func_name = name; // name of function with error
      buffer << "0x" << std::hex << func_ptr;
      std::string address = buffer.str(); // address of function with error
      buffer.str(std::string()); // clear buffer
      std::string error_name;

      // switch over error
      switch(error)
      {
        case GL_INVALID_ENUM:                   error_name = WE_UTIL_STRINGIFY(GL_INVALID_ENUM); break;
        case GL_INVALID_VALUE:                  error_name = WE_UTIL_STRINGIFY(GL_INVALID_VALUE); break;
        case GL_INVALID_OPERATION:              error_name = WE_UTIL_STRINGIFY(GL_INVALID_OPERATION); break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error_name = WE_UTIL_STRINGIFY(GL_INVALID_FRAMEBUFFER_OPERATION); break;
        case GL_STACK_UNDERFLOW:                error_name = WE_UTIL_STRINGIFY(GL_STACK_UNDERFLOW); break;
        case GL_STACK_OVERFLOW:                 error_name = WE_UTIL_STRINGIFY(GL_STACK_OVERFLOW); break;
        case GL_OUT_OF_MEMORY:                  error_name = WE_UTIL_STRINGIFY(GL_OUT_OF_MEMORY); break;
        default:                                error_name = "error"; break;
      }

      message << "[glad_postcall_callback_func]\n";
      message << "Function: " << func_name << '\n';
      message << "Address: " << address << '\n';
      message << "Error: " << error_name << "(" << error << ")\n";
      message << len_args << " arguments passed to erroring function: ";
      
      if(graphics_debug::gl_function_detailed_errors::has_detailed_error_info(func_name))
      {
        auto parameter_types = graphics_debug::gl_function_detailed_errors::param_types(func_name);
        auto parameter_names = graphics_debug::gl_function_detailed_errors::param_names(func_name);

        message << "(";
        va_list l;
        va_start(l, len_args);
        for(int i = 0; i < len_args; ++i)
        {
          if(i != 0)
          {
            message << ",";
          }
          // insert value into stream
          message << parameter_types.at(i) << ' ' << parameter_names.at(i) << '=';
          utils::insert_va_arg_into_sstream(message, parameter_types.at(i), l);
        }
        va_end(l);
        message << ')';
      }
      else
      { 
        message << "Detailed error information is not available for this function";
      }

      log::LOGERROR(message.str());
    }
  }

  std::string opengl_info()
  {
    std::stringstream ss;
    ss << '\n';
    ss << "GL_Vendor: " << (char*)glGetString(GL_VENDOR) << '\n';
    ss << "GL_Renderer: " << (char*)glGetString(GL_RENDERER) << '\n';
    ss << "GL_Version: " << (char*)glGetString(GL_VERSION) << '\n';
    ss << "GL_Shading_Language_Version: " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
    ss << "GL_Extensions: ";

    const char* ext = nullptr;
    ext = (char*)glGetString(GL_EXTENSIONS);
    if (ext)
    {
      ss << ext;
    }
    return ss.str();
  }

  static void release_graphics_assets()
  {
    textures::release_textures();
    textures::release_images();
    shaders::release_shaders();
  }

  void init(std::string title)
  {
    std::stringstream log_stream;
    glfwSetErrorCallback(impl::glfw_error_callback_func); // set glfw callback
    {
      log_stream.str(std::string());
      log_stream << "Set glfw error callback to 0x" << std::hex << impl::glfw_error_callback_func;
      log::LOGTRACE(log_stream.str());
    }
    
    // init glfw
    if(!glfwInit())
    {
      // TODO error handling
      log::LOGERROR("Could not init GLFW!");
    }
    // create initial window
    auto res = resolutions::FHD;
    auto w = create_window(title, res);
    if(!bool(w))
    {
      // TODO error
      log::LOGERROR("Failed to create window!");
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Failed to create window!");
    }
    glfwMakeContextCurrent(w.get()->get()); // set the created window to the active window
    
    // init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      // TODO error and shutdown
      log::LOGERROR("Failed to init GLAD!");
      we::utils::notify(utils::notification_type::mb_ok, "Fatal Error", "Failed to init GLAD!");
    }
    log::LOGDEBUG(opengl_info());

      glad_set_post_callback(impl::glad_postcall_callback_func);
      {
        log_stream.str(std::string());
        log_stream << "Set GLAD postcall callback to 0x" << std::hex << impl::glad_postcall_callback_func;
        log::LOGTRACE(log_stream.str());
      }

    // load shaders
    we::graphics::shaders::load_shaders();

    // for alpha transparency
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void shutdown()
  {
    // release shaders, textures, and images
    release_graphics_assets();
    close_all_windows();
    glfwTerminate();
  }

  void clear()
  {
    window::clear_all();
  }

  void present()
  {
    window::present_all();
  }
}
}