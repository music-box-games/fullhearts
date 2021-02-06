#ifndef _WE_MOUSE_COLLIDER_HPP_
#define _WE_MOUSE_COLLIDER_HPP_

#include "collider.hpp"
#include "input_event.hpp"

namespace waifuengine
{
  namespace ui
  {
    class mouse_collider : public physics::collider
    {
    public:
      COMPONENT_REGISTER(mouse_collider);

      mouse_collider();
      virtual ~mouse_collider();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug();

    private:
      void input_handler(events::event * e);
    };
  }
}

#endif