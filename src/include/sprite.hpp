#ifndef _WE_SPRITE_HPP_
#define _WE_SPRITE_HPP_

#include <component.hpp>
#include <serialization.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class sprite : public component<sprite>
    {
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const version)
      {
        ar & boost::serialization::base_object<component<sprite>>(*this);
      }

    public:
      sprite();
      ~sprite();

      void update(float dt);
      void draw() const;
    };
  }
}

#endif