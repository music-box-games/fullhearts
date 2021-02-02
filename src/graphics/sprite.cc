#include "sprite.hpp"
#include "graphics.hpp"
#include "gameobject.hpp"
#include "log.hpp"

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite(fs::path texture_file) : tex(texture_file), sp(tex.data()) {}
    sprite::~sprite() {}

    void sprite::draw() const 
    {
      get_window_manager().lock()->get_main_window().lock()->data().lock()->draw(sp, parent->get_transform().data().getTransform());
    }

    void sprite::update(float)
    {
      
    }
  }
}