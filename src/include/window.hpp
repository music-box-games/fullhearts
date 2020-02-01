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

#include <memory> // std::unique_ptr, std::weak_ptr
#include <string>

#ifdef WE_GRAPHICS_OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // WE_GRAPHICS_OPENGL

#ifdef WE_GRAPHICS_SDL2
#include <SDL.h>
#include <SDL_image.h>
#endif // WE_GRAPHICS_SDL2

namespace waifuengine
{
  namespace graphics
  {
    namespace opengl
    {
      #ifdef WE_GRAPHICS_OPENGL
      class window_handle
      {
      public:
        using data_type = GLFWwindow;

        window_handle(unsigned width, unsigned height, std::string title);
        ~window_handle();

        data_type * data();

        void clear();
        void render();

      private:
        data_type * window;
      };
      #endif // WE_GRAPHICS_OPENGL
    } // opengl

    namespace sdl2
    {
      #ifdef WE_GRAPHICS_SDL2
      class window_handle
      {
      public:
        using data_type = SDL_Window;

        window_handle(unsigned width, unsigned height, std::string title);
        ~window_handle();

        data_type * data();

        SDL_Renderer * get_renderer();

        void clear();
        void render();

        void set_draw_color(int r, int g, int b, int a);

      private:
        data_type * window;
        SDL_Renderer * renderer;
      };
      #endif // WE_GRAPHICS_SDL2
    } // sdl2

    class window
    {
    public:
      #ifdef WE_GRAPHICS_OPENGL
      using window_type = opengl::window_handle;
      #endif // WE_GRAPHICS_OPENGL
      #ifdef WE_GRAPHICS_SDL2
      using window_type = sdl2::window_handle;
      #endif // WE_GRAPHICS_SDL2
      
      window(unsigned width, unsigned height, std::string title = "");
      ~window();

      std::shared_ptr<window_type> data();

      void clear();
      void render();

      unsigned width() const;
      unsigned height() const;

    private:
      std::shared_ptr<window_type> handle;

      unsigned w;
      unsigned h;
    };
  }
}

#endif // !_WE_WINDOW_HPP_