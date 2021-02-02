#ifndef _WE_DRAWABLE_HPP_
#define _WE_DRAWABLE_HPP_

#include "colors.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class drawable
    {
    public:
      drawable();
      virtual ~drawable();

      virtual void draw() = 0;

    };
  }
}

#endif