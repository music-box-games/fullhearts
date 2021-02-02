#ifndef _WE_SHAPE_HPP_
#define _WE_SHAPE_HPP_

#include "drawable.hpp"

namespace waifuengine
{
  namespace graphics
  {
    template<int vertices>
    class shape : public drawable 
    {
    private:
      int vertcount;

    public:
      shape() : drawable(), vertcount(vertices) {}
      virtual ~shape() {}
      virtual void draw() = 0;

    };
  }
}

#endif