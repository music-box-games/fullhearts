#ifndef _WE_PHYSICS_HPP_
#define _WE_PHYSICS_HPP_

#include <glm/glm.hpp>

#include "component.hpp"

namespace waifuengine
{
  namespace physics
  {
    namespace system
    {
      void set_gravity(float mpssq);
      float get_gravity();
    }

    class physics : public components::component<physics>
    {
    public:
      COMPONENT_REGISTER(physics);

      physics();
      virtual ~physics();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug();

      void set_mass(float m);
      float get_mass() const;

    private:
      float mass; // mass in kg
      
    };
  }
}

#endif