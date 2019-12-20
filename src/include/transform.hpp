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

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <component.hpp>

namespace waifuengine
{
  namespace physics
  {
    class transform : public ::waifuengine::components::component<transform>
    {
    private:
      glm::mat4 matrix;

    public:
      COMPONENT_NAME(transform);
      COMPONENT_TYPE(transform);

      transform();
      transform(transform const& other);
      virtual ~transform();

      virtual void update(float dt) override;
      virtual void draw() const override;

      void rotate(float degrees);
      void translate(glm::vec3 vec);
      void scale(glm::vec3 vec);
    };
  }
}

#endif // !_WE_TRANSFORM_HPP_
