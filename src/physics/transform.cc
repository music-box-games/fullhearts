/******************************************************************************/
/*!
\file   transform.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  transform component for applying transforms to objects.

*/
/******************************************************************************/

#include <transform.hpp>

namespace waifuengine
{
  namespace physics
  {
    transform::transform()
    {
      r.x = 0; r.y = 0; r.w = 0; r.h = 0;
    }
    transform::transform(transform const& other) : r(other.r) {}
    transform::~transform() {}

    void transform::update(float) {}

    void transform::draw() const {}

    void transform::translate(SDL_Rect rect)
    {
      r = rect;
    }

    SDL_Rect transform::translation() const
    {
      return r;
    }

  }
}
