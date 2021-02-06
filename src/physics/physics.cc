#include "physics.hpp"

namespace waifuengine
{
  namespace physics
  {
    namespace system
    {

    }

    physics::physics() : components::component<physics>() {}
    physics::~physics() {}

    void physics::update(float dt)
    {
      // move parent object with forces
    }

    void physics::draw() const
    {

    }

    void physics::draw_debug()
    {

    }

    void physics::set_mass(float m)
    {
      mass = m;
    }

    float physics::get_mass() const
    {
      return mass;
    }
  }
}