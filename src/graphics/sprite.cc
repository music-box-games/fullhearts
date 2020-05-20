#include "sprite.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite() {}
    sprite::~sprite() {}

    void sprite::update(float) {}
    void sprite::draw() const {}
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::graphics::sprite);