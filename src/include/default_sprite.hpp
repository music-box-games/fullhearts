#ifndef _WE_DEFAULT_SPRITE_HPP_
#define _WE_DEFAULT_SPRITE_HPP_

namespace waifuengine
{
  namespace graphics
  {
    class default_sprite
    {
    public:
      default_sprite();
      ~default_sprite();

      void draw() const;
    };
  }
}

#endif