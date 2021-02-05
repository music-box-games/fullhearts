#ifndef _WE_SHAPE_HPP_
#define _WE_SHAPE_HPP_
#include "transform.hpp"
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
      virtual void draw(transform const&) const = 0;

    };
  }
}

#endif