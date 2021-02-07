#include "mouse_collider.hpp"
#include "input.hpp"
#include "transform.hpp"
#include "sprite.hpp"
#include "log.hpp"
#include "event_manager.hpp"
#include "events.hpp"
#include "input_event.hpp"
#include "graphics.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    mouse_collider::mouse_collider() : components::component<mouse_collider>(), colliding(false), col(0,0)
    {
      log::LOGTRACE("Constructing mouse_collider");
      
    }

    mouse_collider::~mouse_collider()
    {
      log::LOGTRACE("Destructing mouse_collider");
    }

    void mouse_collider::update(float dt)
    {
      auto window = graphics::get_main_window().lock();
      auto mp = sf::Mouse::getPosition(*(window->data().lock()));
      glm::vec2 mpos(mp.x, mp.y); 
      // check if mouse is in collider bounds
      colliding = col.check_point(mpos);
    }

    void mouse_collider::draw() const
    {
      
    }

    void mouse_collider::draw_debug()
    {
      if(debugging)
      {

      if(colliding)
      {
        col.draw_debug(graphics::colors::color(0,255,0,255), parent->get_transform());
      }
      else
      {
        col.draw_debug(graphics::colors::color(255,0,0,255), parent->get_transform());
      }
      }
    }

    void mouse_collider::set_dimensions(glm::vec2 d)
    {
      col.set_dimensions(d.x, d.y);
    }

    glm::vec2 mouse_collider::get_dimensions() const
    {
      return col.get_dimensions();
    }

    void mouse_collider::set_position(glm::vec2 p)
    {
      col.set_position(p);
    }

    glm::vec2 mouse_collider::get_position() const
    {
      return col.get_position();
    }

  } // namespace ui
} // namespace waifuengine