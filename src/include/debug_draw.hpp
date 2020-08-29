#ifndef _WE_DEBUG_DRAW_HPP_
#define _WE_DEBUG_DRAW_HPP_

#include <map>

#include "component.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class debug_draw : public components::component<debug_draw>
    {
    private:
      friend class core::debug::imgui_listener;
      std::map<std::string, components::compptr, components::component_sorter> attached_components;

    public:
      COMPONENT_REGISTER(debug_draw);

      debug_draw();
      virtual ~debug_draw();

      virtual void update(float dt);
      virtual void draw() const;
    };
  }
}

#endif