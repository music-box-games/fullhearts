
#ifndef _WE_COLLIDER_HPP_
#define _WE_COLLIDER_HPP_

#include "debug.hpp"
#include "component.hpp"
#include "gameobject.hpp"
#include "shader.hpp"
#include "graphics_primatives.hpp"
#include "transform.hpp"

// TODO: collision layers, only check in layer

namespace waifuengine
{
  namespace physics
  {
    class collider : public waifuengine::components::component<collider>
    {
    protected:
      friend class core::debug::imgui_listener;

      // offset from the parent's transform
      graphics::transform offset;
      // width, height
      glm::vec2 dimensions;
      // if colliding with another object
      bool colliding;

    public:
      COMPONENT_NAME(collider);
      COMPONENT_TYPE(collider);

      collider();
      virtual ~collider();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug() const;

      void offset_translate(glm::vec2 translation);
      void offset_set_translation(glm::vec2 translation);
      glm::vec2 offset_get_translation();

      void offset_rotate(float rotation);
      void offset_set_rotation(float rotation);
      float offset_get_rotation();

      void offset_scale(glm::vec2 scale);
      void offset_set_scale(glm::vec2 scale);
      glm::vec2 offset_get_scale();
      void offset_scalex(float scale);
      void offset_scaley(float scale);
      float offset_get_scalex();
      float offset_get_scaley();

      

      bool is_colliding() const;
    };

    namespace collisions
    {
      bool point_rectangle(glm::vec2 point, graphics::rect_dimensions rect);
    }
  }
}

#endif