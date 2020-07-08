#ifndef _WE_GRAPHICS_PRIMATIVES_HPP_
#define _WE_GRAPHICS_PRIMATIVES_HPP_

#include <array>
#include <glm/glm.hpp>

#include "serialization.hpp"
#include "gameobject.hpp"
#include "shader.hpp"
#include "transform.hpp"

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

      class sized_rectangle : public base_primative
      {
      protected:
        float width = 0.0; // ratio of object_width : window_width
        float height = 0.0; // object_height : window_height
        glm::vec2 center = {0.0f, 0.0f};
        float alpha = 0.5f;
        std::shared_ptr<shaders::shader> shd;
        glm::vec4 color = {0.f, 0.f, 0.f, 1.f};


        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const v)
        {
          ar & boost::serialization::base_object<base_primative>(*this);
          ar & width;
          ar & height;
          ar & center[0];
          ar & center[1];
          ar & alpha;
        }

      public:
        sized_rectangle(std::string name);
        virtual ~sized_rectangle() = default;

        virtual void update(float) override;
        virtual void draw() const override;

        void set_width(float w);
        void set_height(float h);
        void set_center(glm::vec2 c);

        void set_shader(std::string name);

        void set_alpha(float a);
        float get_alpha() const;

        void set_color(glm::vec4 c);
      };

      class triangle : public base_primative
      {
      protected:
        float * vertices;
        int vert_count = 0;
        std::shared_ptr<shaders::shader> shd;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        float width; // width ratio
        float height; // height ratio
        glm::vec2 center; // center point, ratios
        bool calculating_vertices = true;

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

        void set_width(float w); // width compared against total width of window (0-1)
        void set_height(float h);
        void set_center(glm::vec2 c);
        float get_width() const;
        float get_height() const;
        glm::vec2 get_center() const;

        void calculate_vertices(bool set = true);
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
          void serialize(Archive& ar, unsigned int const v)
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