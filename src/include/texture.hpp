#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include <SFML/Graphics.hpp>

#include "debug.hpp"
#include "filesystem.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class texture
    {
    public:
      texture(fs::path file);
      ~texture();

      sf::Texture& data();

    private:
      friend class waifuengine::core::debug::imgui_listener;
      sf::Texture tex;
    };
  }
}

#endif