#ifndef _WE_SPRITE_HPP_
#define _WE_SPRITE_HPP_

#include <component.hpp>
#include <serialization.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class sprite : public components::component<sprite>
    {
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const)
      {
        ar & boost::serialization::base_object<component<sprite>>(*this);
      }

    public:
      COMPONENT_NAME(sprite);
      COMPONENT_TYPE(sprite);
      
      sprite();
      ~sprite();

      void update(float dt);
      void draw() const;
    };
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::graphics::sprite);

#endif