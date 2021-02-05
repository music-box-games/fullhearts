#ifndef _WE_DRAWABLE_HPP_
#define _WE_DRAWABLE_HPP_

#include "colors.hpp"
#include "transform.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class drawable
    {
    public:
      drawable();
      virtual ~drawable();

      virtual void draw(transform const&) const = 0;

    };
  }
}

#endif