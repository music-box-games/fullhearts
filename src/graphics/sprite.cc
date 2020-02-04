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
#include <assets.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite() : components::component<sprite>()
    {
    }
    
    sprite::~sprite() {}

    void sprite::update(float)
    {

    }

    void sprite::draw() const
    {
      im->draw(parent);
    }

    void sprite::link_image(std::string name)
    {
      link_image(we::core::get_image(name));
    }

    void sprite::link_image(std::shared_ptr<image> i)
    {
      im = i;
    }

    void sprite::load_image(std::string file)
    {
      im->load_file(file);
    }

    void sprite::unload_image()
    {
      im->release_image();
    }
  }
}