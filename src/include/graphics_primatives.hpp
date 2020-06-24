#ifndef _WE_GRAPHICS_PRIMATIVES_HPP_
#define _WE_GRAPHICS_PRIMATIVES_HPP_

#include <array>

#include "serialization.hpp"
#include "gameobject.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace primatives
    {
      class base_primative : public waifuengine::object_management::gameobject
      {
      private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const v)
        {
          ar & boost::serialization::base_object<waifuengine::object_management::gameobject>(*this);
        }

      public:
        base_primative(std::string name) : waifuengine::object_management::gameobject(name) {}
        virtual ~base_primative() {}

        virtual void update(float dt) = 0;
        virtual void draw() const = 0;
      };
      BOOST_SERIALIZATION_ASSUME_ABSTRACT(base_primative);

      class triangle : public base_primative
      {
      private:
        std::array<glm::vec2, 3> vertices;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const v)
        {
          ar & boost::serialization::base_object<base_primative>(*this);
          ar & vertices;
        }

      public:
        triangle(std::string name, std::array<glm::vec2, 3> verts);
        virtual ~triangle();

        virtual void update(float dt) override;
        virtual void draw() const override;
      };
    }
  }
}

#endif