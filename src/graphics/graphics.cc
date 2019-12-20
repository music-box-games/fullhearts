/******************************************************************************/
/*!
\file   graphics.cc   
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Graphics namespaces. Handles initialization and shutdown of graphics systems,
  as well as handling different graphics APIs

*/
/******************************************************************************/


#include <iostream>
#include <filesystem>

#include <graphics.hpp>
#include <log.hpp>
#include <return_values.hpp>
#include <log.hpp>
#include <shader.hpp>
#include <utils.hpp>
#include <engine.hpp>
#include <shader.hpp>
#include <texture.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace opengl
    {
      class opengl_manager
      {
      private:
        GLFWwindow * window_; // window handle
        shaders::shader prog_id; // shader program

        GLFWerrorfun error_callback = [](int i, const char * c) -> void { 
          std::stringstream ss;
          const char * err;
          glfwGetError(&err);
          ss << i << ": " << c << " " << err;
          we::log::error(ss.str()); 
          }; // callback for gl errors

        GLFWframebuffersizefun framebuffer_resize_callback = [](GLFWwindow * w, int width, int height) -> void { glViewport(0, 0, width, height); };

        GLFWwindow * create_window()
        {
          glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
          glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
          glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // use opengl version 3.3
          glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // modern core
          //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // forward compat for macos
          return glfwCreateWindow(1024, 768, "Full Hearts", NULL, NULL); // TODO make resolution variable
        }

      public:
        opengl_manager() : window_(NULL) // TODO: make this variable by settings rather than hard coded
        {
          we::log::trace("opengl_manager: constructing");
          if(!glfwInit())
          {
            we::log::error("Failed to init GLFW.");
            return;
          }

          window_ = create_window();
          if(!window_)
          {
            we::log::error("Failed to open GLFW window.");
            glfwTerminate();
            return;
            //return we::core::return_values::glfw_window_fail; // TODO: should use std::exit or some custom function to immediately exit
          }
          // set current context
          glfwMakeContextCurrent(window_);
          
          if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
          {
            we::log::error("Failed to init GLAD");
            glfwTerminate();
            return; // TODO: better error
          }
          // set viewport location and size
          glViewport(0, 0, 1024, 768);

          // set callbacks
          glfwSetErrorCallback(opengl_manager::error_callback);
          glfwSetFramebufferSizeCallback(window_, opengl_manager::framebuffer_resize_callback);

          // load shaders
          shaders::init();
          auto v = we::utils::get_path_relative_to_exe("\\shaders\\vertexshader.vert");
          auto f = we::utils::get_path_relative_to_exe("\\shaders\\fragmentshader.frag");
          prog_id = shaders::shader(v.string(), f.string());

          // load textures
          textures::init();
        }

        ~opengl_manager()
        {
          we::log::trace("opengl_manager: destructing");
          textures::shutdown(); // unload textures
          shaders::shutdown(); // unload shaders
          glfwTerminate();
        }

        void clear()
        {
          we::log::pedantic("opengl_manager: clear");
          glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
        }

        void render()
        {
          we::log::pedantic("opengl_manager: render");

          glfwPollEvents();
          glfwSwapBuffers(window_);
        }

        GLFWwindow * get_window()
        {
          return window_;
        }

        shaders::shader& shader_id()
        {
          return prog_id;
        }
      };


      opengl_manager * glman = nullptr;

      void init()
      {
        we::log::trace("opengl: init");
        glman = new opengl_manager();
      }

      void shutdown()
      {
        we::log::trace("opengl: shutdown");
        delete glman;
        glman = nullptr;
      }

      void clear()
      {
        we::log::pedantic("opengl: clear");
      }

      void render()
      {
        we::log::pedantic("opengl: render");
        glman->render();
      }

      GLFWwindow * get_window()
      {
        return glman->get_window();
      }

      shaders::shader& shader_id()
      {
        return glman->shader_id();
      }
    }

    void init()
    {
      we::log::trace("graphics: init");
      opengl::init();
    }

    void clear()
    {
      we::log::pedantic("graphics: clear");
      opengl::clear();
    }

    void render()
    {
      we::log::pedantic("graphics: render");
      opengl::render();
    }

    void shutdown()
    {
      we::log::trace("graphics: shutdown");
      opengl::shutdown();
    }
  }
}