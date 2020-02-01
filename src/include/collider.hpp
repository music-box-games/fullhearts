#ifndef _WE_COLLIDER_HPP_
#define _WE_COLLIDER_HPP_

#include <component.hpp>

namespace waifuengine
{
  namespace physics
  {
    class transform; // forward declaration
    class collider : public waifuengine::components::component<collider>
    {
    public:
      COMPONENT_NAME(collider);
      COMPONENT_TYPE(collider);

      collider();
      virtual ~collider();

      virtual void update(float dt) = 0;
      virtual void draw() const = 0;

      void reload_transform();

    protected:
       transform * t;
    };
  }
}

#endif