#include <component.hpp>
#include <dummy.hpp>
#include <script_object.hpp>
#include "sprite.hpp"
#include "debug_draw.hpp"
#include "collider.hpp"
#include "mouse_collider.hpp"
#include "component.hpp"

namespace waifuengine
{
  namespace components
  {
    bool component_sorter::operator()(std::string a, std::string b) const
    {
      std::map<std::string, component_order> orders = 
      {
        {graphics::sprite::NAME, component_order::sprite},
        {graphics::debug_draw::NAME, component_order::debug_draw},
        {physics::collider::NAME, component_order::collider},
        {ui::mouse_collider::NAME, component_order::mouse_collider},
        {graphics::transform::NAME, component_order::transform},
      };

      return orders[a] < orders[b];
    }
  }
}
BOOST_CLASS_EXPORT_IMPLEMENT(we::components::component<we::core::scripting::script_object>);