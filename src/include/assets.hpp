#ifndef _WE_ASSETS_HPP_
#define _WE_ASSETS_HPP_

#include <string>
#include <memory>
#include <image.hpp>
#include <text_image.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace assets
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
  }
}

#endif