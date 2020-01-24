/******************************************************************************/
/*!
\file   window.hpp
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  window wrapper class

*/
/******************************************************************************/

#ifndef _WE_WINDOW_HPP_
#define _WE_WINDOW_HPP_

#define WE_GRAPHICS_OPENGL

#ifdef WE_GRAPHICS_OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // WE_GRAPHICS_OPENGL

#ifdef WE_GRAPHICS_SDL2
#include <SDL.h>
#endif // WE_GRAPHICS_SDL2

namespace waifuengine
{
  namespace graphics
  {
    namespace opengl
    {
      class window_handle
      {
      public:
        using data_type = GLFWwindow;

        window_handle();
        ~window_handle();

        data_type * data();

      private:
        data_type * window;
      };
    }

    namespace sdl2
    {
      class window_handle
      {

      };
    }

    class window
    {
    public:
      #ifdef WE_GRAPHICS_OPENGL
      using window_type = opengl::window_handle;
      #endif // WE_GRAPHICS_OPENGL
      #ifdef WE_GRAPHICS_SDL2
      using window_type = sdl2::window_handle;
      #endif // WE_GRAPHICS_SDL2
      
      window();
      ~window();

      window_type * data();

    private:
      window_type * handle;
    };
  }
}

#endif // !_WE_WINDOW_HPP_