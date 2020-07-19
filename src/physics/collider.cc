#include "collider.hpp"
#include "sprite.hpp"
#include "colors.hpp"
#include "log.hpp"
#include "window.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace physics
  {
    collider::collider() : components::component<collider>()
    {
      offset = {0.f, 0.f};
      debug_rect = std::shared_ptr<graphics::primatives::rectangle>(new graphics::primatives::rectangle("collider rect"));
      debug_rect->set_shader("rectangle_primative_shader");
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

    void collider::draw_debug() const
    {
      if (!disabled)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // TODO: draw lines around collider edges, change color based on collision status
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
    }

    void collider::set_offset_from_owner_position(glm::vec2 o)
    {
      offset = o;
    }

    glm::vec2 collider::get_offset_from_owner_position() const
    {
      return offset;
    }

    void collider::set_offset_from_owner_position_x(float x)
    {
      offset = {x, offset.y};
    }

    float collider::get_offset_from_owner_position_x() const
    {
      return offset.x;
    }

    void collider::set_offset_from_owner_position_y(float y)
    {
      offset = {offset.x, y};
    }

    float collider::get_offset_from_owner_position_y() const
    {
      return offset.y;
    }

    void collider::set_dimensions(glm::vec2 d)
    {
      dimensions = d;
    }

    glm::vec2 collider::get_dimensions() const
    {
      return dimensions;
    }

    void collider::set_height(float h)
    {
      dimensions.y = h;
    }

    float collider::get_height() const
    {
      return dimensions.y;
    }

    void collider::set_width(float w)
    {
      dimensions.x = w;
    }

    float collider::get_width() const
    {
      return dimensions.x;
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