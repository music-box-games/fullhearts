#ifndef _WE_ASSETS_HPP_
#define _WE_ASSETS_HPP_

#include <string>
#include <memory>
#include <image.hpp>

namespace waifuengine
{
  namespace core
  {
    void load_images(std::string ilist);

    std::shared_ptr<waifuengine::graphics::image> get_image(std::string name);
    void remove_image(std::string name);

    namespace assets
    {
      void init();
      void shutdown();
    }
  }
}

#endif