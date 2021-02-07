#ifndef _WE_MOUSE_COLLIDER_HPP_
#define _WE_MOUSE_COLLIDER_HPP_

#include "collider.hpp"
#include "input_event.hpp"
#include "bounding_box.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace ui
  {
    class mouse_collider : public components::component<mouse_collider>
    {
    public:
      COMPONENT_REGISTER(mouse_collider);

      mouse_collider();
      virtual ~mouse_collider();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug();

      void set_dimensions(glm::vec2 d);
      glm::vec2 get_dimensions() const;
      void set_position(glm::vec2 p);
      glm::vec2 get_position() const;

    private:
      friend class core::debug::imgui_listener;
      bool colliding;
      graphics::bounding_box col;
    };
  }
}

#endif