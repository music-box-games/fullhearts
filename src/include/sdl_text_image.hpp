#ifndef _WE_SDL_TEXT_IMAGE_HPP_
#define _WE_SDL_TEXT_IMAGE_HPP_

#ifndef WE_GRAPHICS_SDL2

#include <string>

namespace waifuengine
{
  namespace graphics
  {
    namespace sdl2
    {
      class text_image_handle
      {
      public:
        text_image_handle();
        text_image_handle(std::string t);
        text_image_handle(text_image_handle const& other);
        ~text_image_handle();

        void text(std::string t);
        std::string text() const;

        void draw() const;
        
      private:
        std::string t_;
      };
    }
  }
}

#endif
#endif