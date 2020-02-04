#ifndef _WE_FONT_HPP_
#define _WE_FONT_HPP_

#ifdef WE_GRAPHICS_SDL2
#include <sdl_text.hpp>
#endif

#include <memory>

namespace waifuengine
{
  namespace graphics
  {
    class font
    {
    public:
      #ifdef WE_GRAPHICS_SDL2
      using font_handle = sdl::font;
      #endif
      font(std::string path_to_font, int pt);
      ~font();

      std::shared_ptr<font_handle> data();

    private:
      std::shared_ptr<font_handle> handle;
    };
  }
}

#endif