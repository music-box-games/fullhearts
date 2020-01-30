#ifndef _WE_TEXT_IMAGE_HPP_
#define _WE_TEXT_IMAGE_HPP_

#include <string>

#ifdef WE_GRAPHICS_SDL2
#include <sdl_text_image.hpp>
#endif

namespace waifuengine
{
  namespace graphics
  {
    class text_image
    {
    public:
      #ifdef WE_GRAPHICS_SDL
      using handle_type = sdl2::text_image_handle;
      #endif

      text_image();
      text_image(std::string text);
      text_image(text_image const& other);
      ~text_image();

      void text(std::string t);
      std::string text() const;

      void draw() const;

    private:
      handle_type handle;
    };
  }
}

#endif