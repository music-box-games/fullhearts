#ifndef _WE_SDL_TEXT_IMAGE_HPP_
#define _WE_SDL_TEXT_IMAGE_HPP_

#ifdef WE_GRAPHICS_SDL2

#include <SDL.h>

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
        #ifdef WE_GRAPHICS_SDL2
        using image_type = SDL_Texture
        #endif
        text_image_handle(std::string t);
        ~text_image_handle();

        void draw(void * parent) const;
        
      private:
        std::string t_;
        image_type * data;
      };
    }
  }
}

#endif
#endif