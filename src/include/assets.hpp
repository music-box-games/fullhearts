#ifndef _WE_ASSETS_HPP_
#define _WE_ASSETS_HPP_

#include <string>
#include <memory>
#include <image.hpp>
#include <font.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class text_image;
  }

  namespace core
  {
    namespace image_assets
    {
      void load_images(std::string ilist);
      std::shared_ptr<waifuengine::graphics::image> get_image(std::string name);
      void remove_image(std::string name);
      void init();
      void shutdown();
    }

    namespace text_assets
    {
      std::shared_ptr<waifuengine::graphics::text_image> get_text(std::string text);
      void unload_text(std::string text);
      void init();
      void shutdown();
    }

    namespace font_assets
    {
      void load_fonts(std::string flist);
      std::shared_ptr<waifuengine::graphics::font> get_font(std::string name);
      void unload_font(std::string name);
      void init();
      void shutdown();
      std::shared_ptr<waifuengine::graphics::font> default_font();
    }

    namespace assets
    {
      void init();
      void shutdown();
    }
  }
}

#endif