#ifndef _WE_TEXT_IMAGE_HPP_
#define _WE_TEXT_IMAGE_HPP_

#include <string>
#include <memory>

#ifdef WE_GRAPHICS_SDL2
#include <sdl_text_image.hpp>
#endif

#include <string>
#include <memory>

#include <font.hpp>

#include <assets.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class text_image
    {
    public:
      #ifdef WE_GRAPHICS_SDL2
      using handle_type = sdl2::text_image_handle;
      #endif

      text_image(std::string text, std::shared_ptr<waifuengine::graphics::font> font = waifuengine::core::font_assets::default_font());
      ~text_image();

      void draw(void * parent);
      std::shared_ptr<handle_type> get_handle();

    private:
      std::shared_ptr<handle_type> handle;
    };
  }
}

#endif