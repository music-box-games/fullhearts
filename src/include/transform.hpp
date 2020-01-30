/******************************************************************************/
/*!
\file   transform.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Transform components for transforms.

*/
/******************************************************************************/

#ifndef _WE_TRANSFORM_HPP_
#define _WE_TRANSFORM_HPP_

#include <SDL.h>

#include <component.hpp>
// TODO: make this not SDL specific
namespace waifuengine
{
  namespace physics
  {
    class transform : public ::waifuengine::components::component<transform>
    {
    private:
      SDL_Rect r;

    public:
      COMPONENT_NAME(transform);
      COMPONENT_TYPE(transform);

      transform();
      transform(transform const& other);
      virtual ~transform();

      virtual void update(float dt) override;
      virtual void draw() const override;

      void translate(SDL_Rect r);

      SDL_Rect translation() const;
    };
  }
}

#endif // !_WE_TRANSFORM_HPP_
