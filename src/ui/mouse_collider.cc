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
    mouse_collider::mouse_collider() : physics::collider()
    {
      log::LOGTRACE("Constructing mouse_collider");
      // sign up for mouse click events
      auto f = std::bind(&mouse_collider::input_handler, this, std::placeholders::_1);
      events::subscribe<graphics::input::input_event>(this, f);
    }

    mouse_collider::~mouse_collider()
    {
      log::LOGTRACE("Destructing mouse_collider");
      events::unsubcribe<graphics::input::input_event>(this);
    }

    void mouse_collider::update(float dt)
    {
      auto window = graphics::get_main_window().lock();
      glm::vec2 mpos = sf::Mouse::getPosition(*(window->data().lock()));
      // check if mouse is in collider bounds
      // 
    }

    void mouse_collider::input_handler(events::event * e)
    {

    }
  } // namespace ui
} // namespace waifuengine