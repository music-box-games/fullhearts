#include "font.hpp"
#include "log.hpp"

namespace waifuengine
{
  namespace graphics
  {
    font::font(std::string name) : name_(name)
    {
    }

    font::~font() {}

    bool font::load(std::string filename)
    {
      if(!font_.loadFromFile(filename))
      {
        log::LOGERROR(std::string("Failed to load font file: " + filename));
        return false;
      }
      else
      {
        log::LOGTRACE(std::string("Loaded font file: " + filename));
        return true;
      }
    }

    sf::Font const& font::data() const
    {
      return font_;
    }

    sf::Font& font::data()
    {
      return font_;
    }

    std::string font::name() const
    {
      return name_;
    }
  }
}