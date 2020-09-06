#include "debug_draw.hpp"
#include "sprite.hpp"
#include "collider.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    debug_draw::debug_draw() : components::component<debug_draw>()
    {

    }

    debug_draw::~debug_draw()
    {

    }

    void debug_draw::update(float) 
    {
      if(!disabled)
      {
        attached_components.clear();
        // collect pointers to the components we want to draw
        // transform
        // TODO: transform still isn't an object wide component oops
        // auto trptr = parent->get_component<transform>();
        // if(trptr)
        // {
        //   attached_components[transform::NAME] = trptr;
        // }
        // sprite
        auto spptr = parent->get_component<sprite>();
        if(spptr)
        {
          attached_components[sprite::NAME] = spptr;
        }
        // rigidbody
        // collider
        auto colptr = parent->get_component<physics::collider>();
        if(colptr)
        {
          attached_components[physics::collider::NAME] = colptr;
        }
      }
    }

    void debug_draw::draw() const
    {
      std::for_each(attached_components.begin(), attached_components.end(), [](auto pair) -> void
      {
        pair.second->draw_debug();
      });
    }
  }
}