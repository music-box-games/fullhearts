#ifndef _WE_COLLIDER_HPP_
#define _WE_COLLIDER_HPP_

#include <component.hpp>
#include <serialization.hpp>

namespace waifuengine
{
  namespace physics
  {
    class collider : public waifuengine::components::component<collider>
    {
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const version)
      {
        ar & ::boost::serialization::base_object<waifuengine::components::component<collider>(*this);
      }

    public:
      COMPONENT_NAME(collider);
      COMPONENT_TYPE(collider);

      collider();
      virtual ~collider();

      virtual void update(float dt) = 0;
      virtual void draw() const = 0;
    };
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::physics::collider);

#endif