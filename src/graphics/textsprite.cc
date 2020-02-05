/******************************************************************************/
/*!
\file   textsprite.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Special sprite for rendered text

*/
/******************************************************************************/

#include <textsprite.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  textsprite::textsprite() : we::components::component<textsprite>() {}
  textsprite::~textsprite() {}

  void textsprite::update(float)
  {

  }

  void textsprite::draw() const
  {
    ti->draw(parent);
  }

  void textsprite::set_text(std::string t)
  {
    ti.reset();
    ti = std::shared_ptr<text_image>(new text_image(t));
  }
}
} // namespace waifuengine