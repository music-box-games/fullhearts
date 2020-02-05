#ifndef _WE_SDL_TEXT_IMAGE_HPP_
#define _WE_SDL_TEXT_IMAGE_HPP_

#ifdef WE_GRAPHICS_SDL2

#include <SDL.h>

#include <string>

#include <font.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace sdl2
    {
      class text_image_handle
      {
      public:
        using image_type = SDL_Texture;
        text_image_handle(std::string t, std::shared_ptr<waifuengine::graphics::font> f);
        ~text_image_handle();

        void draw(void * parent) const;
        
      private:
        std::string t_;
        std::shared_ptr<waifuengine::graphics::font> f_;
        image_type * data;
      };
    }
  }
}

#endif
#endif