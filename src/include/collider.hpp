
#ifndef _WE_COLLIDER_HPP_
#define _WE_COLLIDER_HPP_

#include "component.hpp"
#include "gameobject.hpp"
#include "shader.hpp"
#include "graphics_primatives.hpp"

namespace waifuengine
{
  namespace physics
  {
    class collider : public waifuengine::components::component<collider>
    {
    protected:

      glm::vec2 offset;
      glm::vec2 dimensions;

      bool colliding;

        std::shared_ptr<graphics::primatives::sized_rectangle> debug_rect;

    public:
      COMPONENT_NAME(collider);
      COMPONENT_TYPE(collider);

      collider();
      virtual ~collider();

      virtual void update(float dt);
      virtual void draw() const;

      void set_offset_from_owner_position(glm::vec2 o);
      glm::vec2 get_offset_from_owner_position() const;
      void set_offset_from_owner_position_x(float x);
      float get_offset_from_owner_position_x() const;
      void set_offset_from_owner_position_y(float y);
      float get_offset_from_owner_position_y() const;


      void set_dimensions(glm::vec2 d);
      glm::vec2 get_dimensions() const;
      void set_width(float w);
      float get_width() const;
      void set_height(float h);
      float get_height() const;
    };

    namespace collisions
    {
      bool point_rectangle(glm::vec2 point, graphics::rect_dimensions rect);
    }
  }
}

#endif