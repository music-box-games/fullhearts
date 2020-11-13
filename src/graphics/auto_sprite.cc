#include "auto_sprite.hpp"

#include "sprite.hpp"
#include "default_sprite.hpp"

namespace waifuengine
{
  namespace graphics
  {
    auto_sprite::auto_sprite() : sp({}), loaded(false), default_sp({}) {}
    auto_sprite::auto_sprite(std::weak_ptr<sprite> s) : sp(s), loaded(true), default_sp({}) {}
    auto_sprite::~auto_sprite()
    {
      // TODO: delete default sprite
    }

    void auto_sprite::load(std::weak_ptr<sprite> s)
    {
      sp = s;
      loaded = true;
    }

    void auto_sprite::unload()
    {
      loaded = false;
    }

    void auto_sprite::draw() const
    {
      (loaded) ? sp.lock()->draw() : default_sp.draw();
    }
  }
}