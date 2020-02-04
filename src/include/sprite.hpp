/******************************************************************************/
/*!
\file   sprite.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Sprite class.

*/
/******************************************************************************/

#ifndef _WE_SPRITE_HPP_
#define _WE_SPRITE_HPP_

#include <component.hpp>
#include <image.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class sprite : public components::component<sprite>
    {
    public:
      COMPONENT_NAME(sprite);
      COMPONENT_TYPE(sprite);

      sprite();
      virtual ~sprite();

      virtual void update(float dt);
      virtual void draw() const;

      void load_image(std::string file);
      void unload_image();

      void link_image(std::string name);
      void link_image(std::shared_ptr<image> i);
    private:
      std::shared_ptr<image> im;
    };
  }
}

#endif // !_WE_SPRITE_HPP_