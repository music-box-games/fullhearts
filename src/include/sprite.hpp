#ifndef _WE_SPRITE_HPP_
#define _WE_SPRITE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include "texture.hpp"
#include "component.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class sprite : public components::component<sprite> 
    {
    public:
      COMPONENT_REGISTER(sprite);

      sprite(fs::path texture_file);
      virtual ~sprite();

      virtual void update(float dt);
      virtual void draw() const;

    private:
      friend class waifuengine::core::debug::imgui_listener;
      texture tex;
      sf::Sprite sp;
    };
  }
}

#endif