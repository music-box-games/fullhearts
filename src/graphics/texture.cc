/******************************************************************************/
/*!
\file   texture.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Texture class

*/
/******************************************************************************/

#include <SOIL2/SOIL2.h>

#include <texture.hpp>
#include <log.hpp>

namespace waifuengine
{
  namespace graphics
  {
    texture::texture() : texture_id(0) {}

    texture::texture(std::string file)
    {
      load_texture(file);
    }

    texture::texture(texture const& other)
    {
      texture_id = other.texture_id;
    }

    texture::~texture()
    {

    }

    void load_texture(std::string file)
    {
      texture_id = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
      // check that loading worked properly
      if(texture_id == 0)
      {
        std::stringstream ss;
        ss << "Failed to load texture: " << file;
        we::log::error(ss.str());
        return;
      }
    }
  }
}