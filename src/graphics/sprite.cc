/******************************************************************************/
/*!
\file   sprite.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Sprite class. Contains and manages shaders and textures.

*/
/******************************************************************************/

#include <sprite.hpp>

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite() : components::component<sprite>()
    {
      im.set_parent(this);
    }
    
    sprite::~sprite() {}

    void sprite::update(float)
    {

    }

    void sprite::draw() const
    {
      im.draw();
    }

    void sprite::load_image(std::string file)
    {
      im.load_file(file);
    }

    void sprite::unload_image()
    {
      im.release_image();
    }
  }
}