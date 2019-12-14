// this file was written following this tutorial: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <graphics.hpp>
#include <log.hpp>
#include <return_values.hpp>
#include <log.hpp>

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
        GLFWwindow * window_;

        GLFWerrorfun error_callback = [](int i, const char * c) -> void { we::log::error(c); };

      public:
        opengl_manager() : window_(glfwCreateWindow(1024, 768, "Full Hearts", NULL, NULL)) // TODO: make this variable by settings rather than hard coded
        {
          glfwSetErrorCallback(opengl_manager::error_callback);
          if(!glfwInit())
          {
            we::log::error("Failed to init GLFW.");
            return;
          }

          we::log::trace("graphics init");
          glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
          glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set glfw version to 3.3
          glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
          glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
          glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // assure modern glfw/opengl

          window_ = glfwCreateWindow(1024, 768, "Full Hearts", NULL, NULL);

          if(!window_)
          {
            we::log::error("Failed to open GLFW window.");
            glfwTerminate();
            return;
            //return we::core::return_values::glfw_window_fail; // TODO: should use std::exit or some custom function to immediately exit
          }
          // set current context
          glfwMakeContextCurrent(window_);
          if(glewInit() != GLEW_OK)
          {
            we::log::error("Failed to init GLEW.");
            return; // TODO: also exit from here
          }

        }

        ~opengl_manager()
        {

        }

        void update(float dt)
        {

        }

        void draw() const
        {

        }
      };


      opengl_manager * glman = nullptr;

      void init()
      {
        glman = new opengl_manager();
      }

      void shutdown()
      {
        delete glman;
        glman = nullptr;
      }
    }
  }
}