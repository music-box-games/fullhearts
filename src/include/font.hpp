#ifndef _WE_FONT_HPP_
#define _WE_FONT_HPP_

#include <string>
#include <SFML/Graphics.hpp>
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class font
    {
    public:
      font(std::string name);
      ~font();
      bool load(std::string filename);
      
      sf::Font const& data() const;
      sf::Font& data();

      std::string name() const;

    private:
      friend class core::debug::imgui_listener;
      std::string name_;
      sf::Font font_;
    };
  }
}

#endif