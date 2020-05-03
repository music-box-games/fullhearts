#include <component.hpp>
#include <dummy.hpp>
#include <physics.hpp>
#include <collider.hpp>
#include <script_object.hpp>

namespace waifuengine
{
  namespace components
  {
  }
}
BOOST_CLASS_EXPORT_IMPLEMENT(we::components::component<we::components::dummy>);
BOOST_CLASS_EXPORT_IMPLEMENT(we::components::component<we::physics::collider>);
BOOST_CLASS_EXPORT_IMPLEMENT(we::components::component<we::core::scripting::script_object>);