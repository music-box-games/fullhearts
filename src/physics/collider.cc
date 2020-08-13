#include "collider.hpp"
#include "sprite.hpp"
#include "colors.hpp"
#include "log.hpp"
#include "window.hpp"
#include "draw_rects.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace physics
  {
    collider::collider() : components::component<collider>()
    {
    }

    collider::~collider()
    {
    }

    void collider::update(float dt)
    {
      if(!disabled)
      {
        // TODO: decide if checking collisions here or all at once in a different update function
      }
    }

    void collider::draw() const
    {
    }

    bool collider::is_colliding() const
    {
      return colliding;
    }

    void collider::draw_debug()
    {
      if (!disabled && debugging)
      {
        glm::vec2 initial_position(0,0);
        auto parent_transform = parent->get_component<graphics::transform>();
        if(parent_transform.use_count())
        {
          graphics::transform * trf = dynamic_cast<graphics::transform *>(parent_transform.get());
          if(trf)
          {
            initial_position = trf->translate();
          }
        }
        offset.set_translation(initial_position);
      }
    }

    void collider::offset_translate(glm::vec2 translation)
    {
      offset.translate(translation);
    }

    void collider::offset_set_translation(glm::vec2 translation)
    {
      offset.set_translation(translation);
    }

    glm::vec2 collider::offset_get_translation()
    {
      return offset.translate();
    }

    void collider::offset_rotate(float degrees)
    {
      offset.rotate(degrees);
    }

    void collider::offset_set_rotation(float degrees)
    {
      offset.set_rotation(degrees);
    }

    float collider::offset_get_rotation()
    {
      return offset.rotate();
    }

    void collider::offset_scale(glm::vec2 s)
    {
      offset.scale(s);
    }

    void collider::offset_set_scale(glm::vec2 s)
    {
      offset.set_scale(s);
    }

    glm::vec2 collider::offset_get_scale()
    {
      return offset.scale();
    }

    void collider::offset_scalex(float s)
    {
      offset_scale(glm::vec2(s, offset_get_scaley()));
    }

    void collider::offset_scaley(float sy)
    {
      offset_scale(glm::vec2(offset_get_scalex(), sy));
    }

    float collider::offset_get_scalex()
    {
      return offset.scale().x;
    }

    float collider::offset_get_scaley()
    {
      return offset.scale().y;
    }



    namespace collisions
    {
      bool point_rectangle(glm::vec2 point, graphics::rect_dimensions rect)
      {
        if (point.x < rect.vertices[0].x)
        {
          return false;
        }
        else if (point.x > rect.vertices[1].x)
        {
          return false;
        }
        else if (point.y > rect.vertices[1].y)
        {
          return false;
        }
        else if (point.y < rect.vertices[2].y)
        {
          return false;
        }
        return true;
      }
    } // namespace collisions
  }   // namespace physics
} // namespace waifuengine