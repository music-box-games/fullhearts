/******************************************************************************/
/*!
\file   button_collider.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Collider component for buttons

*/
/******************************************************************************/

#include <button_collider.hpp>
#include <event_manager.hpp>
#include <input_event.hpp>
#include <input.hpp>
#include <transform.hpp>
#include <graphics.hpp>
#include <debug_draw.hpp>
#include <sprite.hpp>

// TODO: make this less dependant on SDL

#include <SDL.h>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace physics
{
  button_collider::button_collider() : collider(), hover(false), himage(""), nhimage("")
  {
    auto bound = std::bind(&button_collider::input_handler, this, std::placeholders::_1);
    we::events::subscribe<we::input::input_event>(this, bound);
  }

  button_collider::~button_collider()
  {
    we::events::unsubcribe<we::input::input_event>(this);
  }

  void button_collider::update(float)
  {
    if(!t)
    {
      reload_transform();
    }
    // TODO: check for hover
    int x, y;
    SDL_GetMouseState(&x, &y);
    auto * sp = dynamic_cast<we::graphics::sprite *>(parent->get_component<we::graphics::sprite>().get());
    bool prevhover = hover;
    if (check_point_collision(x, y))
    {
      hover = true;
      if ((!himage.empty()) && prevhover != hover)
      {
        sp->link_image(himage); // link hover image
      }
    }
    else
    {
      hover = false;
      if (prevhover != hover)
      {
        sp->link_image(nhimage);
      }
    }
  }

  void button_collider::set_hover_image(std::string name)
  {
    himage = name;
  }

  void button_collider::set_nonhover_image(std::string name)
  {
    nhimage = name;
  }

  void button_collider::draw() const
  {
    // if debug and draw, draw
    // TODO: maybe build a special class that handles debug drawing lines like this
    if (!t) return;
    SDL_Rect r = t->get();
    int cr, cb, cg, ca;
    if (hover)
    {
      cr = 0xFF;
      cb = 0xEC;
      cg = 0x45;
      ca = 0xFF;
    }
    else
    {
      cr = 0xFF;
      cb = 0x0;
      cg = 0x0;
      ca = 0xFF;
    }
    // top line
    int dx1, dx2, dy1, dy2;
    get_line(1, &dx1, &dy1, &dx2, &dy2);
    we::graphics::debug::add_debug_line(dx1, dy1, dx2, dy2, cr, cb, cg, ca);
    // right line
    get_line(2, &dx1, &dy1, &dx2, &dy2);
    we::graphics::debug::add_debug_line(dx1, dy1, dx2, dy2, cr, cb, cg, ca);
    // bottom line                      
    get_line(3, &dx1, &dy1, &dx2, &dy2);
    we::graphics::debug::add_debug_line(dx1, dy1, dx2, dy2, cr, cb, cg, ca);
    // right line                       
    get_line(4, &dx1, &dy1, &dx2, &dy2);
    we::graphics::debug::add_debug_line(dx1, dy1, dx2, dy2, cr, cb, cg, ca);
  }

  void button_collider::set_trigger(std::function<void()> func)
  {
    f = func;
  }

  void button_collider::input_handler(we::events::event * e)
  {
    if(!t) return;
    we::input::input_event * ie = dynamic_cast<we::input::input_event *>(e);
    if(ie->key == we::input::keys::MOUSE1 && ie->type == we::input::input_type::PRESS)
    {
      // check for collision with mouse
      int x, y;
      we::input::get_mouse_position(&x, &y);
      if(check_point_collision(x, y))
      {
        f();
      }
    }
  }

  bool button_collider::check_point_collision(int const& x, int const& y)
  {
    bool result = true;

    int x1, x2, y1, y2;

    // if above top line
    get_line(1, &x1, &y1, &x2, &y2);
    if (y < y1)
    {
      result = false;
    }
    // if outside right side
    get_line(2, &x1, &y1, &x2, &y2);
    if (x > x1)
    {
      result = false;
    }
    // if below bottom side
    get_line(3, &x1, &y1, &x2, &y2);
    if (y > y1)
    {
      result = false;
    }
    // if outside left side
    get_line(4, &x1, &y1, &x2, &y2);
    if (x < x1)
    {
      result = false;
    }
    return result;
  }

  void button_collider::get_line(int line, int* x1, int* y1, int* x2, int* y2) const
  {
    SDL_Rect r = t->get();
    switch (line)
    {
    case 1:
      // top line
      *x1 = r.x - (r.w / 2);
      *x2 = r.x + (r.w / 2);
      *y1 = r.y - (r.h / 8);
      *y2 = r.y - (r.h / 8);
      break;
    case 2:
      // right line
      *x1 = r.x + (r.w / 2);
      *x2 = r.x + (r.w / 2);
      *y1 = r.y - (r.h / 8);
      *y2 = r.y + (r.h / 8);
      break;
    case 3:
      // bottom line
      *x1 = r.x + (r.w / 2);
      *x2 = r.x - (r.w / 2);
      *y1 = r.y + (r.h / 8);
      *y2 = r.y + (r.h / 8);
      break;
    case 4:
       // left line
      *x1 = r.x - (r.w / 2);
      *x2 = r.x - (r.w / 2);
      *y1 = r.y + (r.h / 8);
      *y2 = r.y - (r.h / 8);
      break;
    default:
      *x1 = 0;
      *x2 = 0;
      *y1 = 0;
      *y2 = 0;
      break;
    }
  }

}
}