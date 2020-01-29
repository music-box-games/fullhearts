/******************************************************************************/
/*!
\file   image.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Image wrapper for different libraries

*/
/******************************************************************************/

#ifndef _WE_IMAGE_HPP_
#define _WE_IMAGE_HPP_

#include <memory>

#ifdef WE_GRAPHICS_SDL2
#include <s_image.hpp>
#endif // WE_GRAPHICS_SDL2

namespace waifuengine
{
  namespace graphics
  {
    class image
    {
    public:
      #ifdef WE_GRAPHICS_SDL2
      using handle_type = sdl2::image_handle;
      #endif // WE_GRAPHICS_SDL2

      image();
      ~image();

      void load_file(std::string file);
      void release_image();
      std::shared_ptr<handle_type> get_handle();

      bool valid() const;

      void draw() const;

      void set_parent(void * p);
      void * get_parent();

    private:
      std::shared_ptr<handle_type> handle;
      void * parent;
    };
  }
}

#endif // !_WE_IMAGE_HPP_