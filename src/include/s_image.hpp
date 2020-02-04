#ifndef _WE_S_IMAGE_HPP_
#define _WE_S_IMAGE_HPP_

#ifdef WE_GRAPHICS_SDL2

#include <string>

#include <SDL.h>

namespace waifuengine
{
  namespace graphics
  {
    class image;

    namespace sdl2
    {
      class image_handle
      {
      public:
        using image_type = SDL_Texture;
        
        image_handle();
        ~image_handle();

        void load_image(std::string file);
        image_type * get_image();

        void release_image();

        bool valid() const;

        void draw(void * parent) const;

      private:
        image_type * data;
      };
    }
  }
}

#endif // WE_GRAPHICS_SDL2

#endif // !_WE_S_IMAGE_HPP_