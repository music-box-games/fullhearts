#include "mouse_collider.hpp"
#include "input.hpp"
#include "transform.hpp"
#include "sprite.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    mouse_collider::mouse_collider() : physics::collider()
    {
      // sign up for mouse click events
      log::LOGTRACE("Constructing mouse_collider");
    }

    mouse_collider::~mouse_collider()
    {
      log::LOGTRACE("Destructing mouse_collider");
    }

    void mouse_collider::update(float dt)
    {
     
    }
  } // namespace ui
} // namespace waifuengine