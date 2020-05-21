#include "texture.hpp"
#include <SOIL/SOIL.h>


namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    texture::texture(fs::path file) : txtr(0)
    {
      load(file);
    }

    texture::~texture()
    {
    }

    void texture::draw() const
    {
    }

    void texture::load(fs::path file)
    {
      txtr = SOIL_load_OGL_texture(file.string().c_str(), SOIL_LOAD_AUTO, ((txtr == 0) ? SOIL_CREATE_NEW_ID : txtr),
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
      if(txtr == 0)
      {
        // make default texture
      }
      float vertices[] = {
        // positions       // colors          // texture coords
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
        0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left
      };
    }
  } // namespace graphics
} // namespace waifuengine