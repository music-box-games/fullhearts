#ifndef _WE_SDL_TEXT_HPP_
#define _WE_SDL_TEXT_HPP_

#include <string>

#include <SDL_ttf.h>

namespace waifuengine
{
  namespace graphics
  {
    namespace sdl
    {
      class font
      {
      public:
        using data_type = TTF_Font;

        font(std::string path_to_font, int pt);
        ~font();

        data_type * data();

      private:
        data_type * fd;
      };
    }
  }
}

#endif