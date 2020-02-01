#include <collider.hpp>
#include <log.hpp>
#include <transform.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace physics
{
  collider::collider() : we::components::component<collider>(), t(nullptr)
  {
    reload_transform();
    if(!t)
    {
      we::log::warning("Collider attached to object without a transform!");
    }
  }

  collider::~collider() {}

  void collider::reload_transform()
  {
    if (!parent) return;
    auto trans = parent->get_component<transform>();
    if(trans.use_count() == 0)
    {
      // no transform
    }
    else
    {
      t = dynamic_cast<transform *>(trans.get());
    }
  }
}
} // namespace waifuengine