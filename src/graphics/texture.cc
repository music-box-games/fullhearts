#include "texture.hpp"

namespace waifuengine
{
  namespace graphics
  {
    texture::texture(fs::path file) 
    {
      tex.loadFromFile(file.string());
    }

    texture::~texture()
    {

    }

    sf::Texture texture::data()
    {
      return tex;
    }
  }
}