#ifndef _WE_GRAPHICS_PRIMATIVES_HPP_
#define _WE_GRAPHICS_PRIMATIVES_HPP_

#include <array>
#include <glm/glm.hpp>

#include "serialization.hpp"
#include "gameobject.hpp"
#include "shader.hpp"

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
      protected:
        float * vertices;
        int vert_count = 0;
        std::shared_ptr<shaders::shader> shd;
        unsigned int VAO;
        unsigned int VBO;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const v)
        {
          ar & boost::serialization::base_object<base_primative>(*this);
          ar & vertices;
        }

      public:
        triangle(std::string name);
        virtual ~triangle();

        virtual void update(float dt) override;
        virtual void draw() const override;

        void set_vertices(float * verts, int length);
        void set_shader(std::string name);
      };
    }

    namespace shaders
    {
      namespace test
      {
        class test_triangle0 : public primatives::triangle
        {
        protected:
          friend class boost::serialization::access;
          template<class Archive>
          void serialize(Archive& ar, unsigned int const v)
          {
            ar & boost::serialization::base_object<primatives::triangle>(*this);
          }

        public:
          test_triangle0(std::string name);
          virtual ~test_triangle0() = default;
        };

        class test_triangle1 : public primatives::triangle
        {
        protected:
          friend class boost::serialization::access;
          template<class Archive>
          void serialization(Archive& ar, unsigned int const v)
          {
            ar & boost::serialization::base_object<primatives::triangle>(*this);
          }

        public:
          test_triangle1(std::string name);
          virtual ~test_triangle1() = default;

          virtual void draw() const override;

        };
      }
    }
  }
}

#endif