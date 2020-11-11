#ifndef _WE_AUTOSPRITE_HPP_
#define _WE_AUTOSPRITE_HPP_

#include <memory>

#include "default_sprite.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class sprite;
    class default_sprite;

    class auto_sprite
    {
    public:
      std::weak_ptr<sprite> sp;
      bool loaded;
      default_sprite default_sp;

      auto_sprite();
      auto_sprite(std::weak_ptr<sprite> s);
      ~auto_sprite();

      void load(std::weak_ptr<sprite> s);
      void unload();

      void draw() const;
    };
  }
}

#endif