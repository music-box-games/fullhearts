#include "mouse_collider.hpp"
#include "input.hpp"
#include "transform.hpp"
#include "sprite.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    mouse_collider::mouse_collider() : physics::collider()
    {
      // sign up for mouse click events
    }

    mouse_collider::~mouse_collider()
    {
    }

    void mouse_collider::update(float dt)
    {
      glm::vec2 reference_point{0.0f, 0.0f}; // reference point to offset from
      if (parent)
      {
        // TODO: objects without sprites should still have transforms
        // set ref point to owner's position
        auto spr = parent->get_component<graphics::sprite>();
        if (spr.use_count())
        {
          auto s = dynamic_cast<graphics::sprite *>(spr.get());
          reference_point = s->translate();
        }
        reference_point += offset;
        auto mouse_pos = graphics::input::mouse_position();
        auto dm = graphics::rect_dimensions(reference_point, dimensions);
        colliding = physics::collisions::point_rectangle(mouse_pos, dm);
                debug_rect->set_center(reference_point);
        debug_rect->set_width(dimensions.x);
        debug_rect->set_height(dimensions.y);
      }
      debug_rect->update(dt);
    }
  } // namespace ui
} // namespace waifuengine