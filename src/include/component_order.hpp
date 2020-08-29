#ifndef _WE_COMPONENT_ORDER_HPP_
#define _WE_COMPONENT_ORDER_HPP_

namespace waifuengine
{
  namespace components
  {
    namespace order
    {

    enum component_order
    {
      sprite = 0,
      physics,
      physics2,
      transform,
      collider,
      mouse_collider,
      script_object,
      dummy,
      debug_draw, // should be last so it can draw on top of everything
    };
    }
  }
}

#endif