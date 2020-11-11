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
    static std::map<std::string, int> orders;

    void component_sorter::register_component(std::string a, int b)
    {
      if(!orders.count(a))
      {
        orders[a] = b;
      }
    }

    bool component_sorter::operator()(std::string a, std::string b) const
    {
      return orders[a] < orders[b];
    }
  }
}