#include <vector>

#include <debug_draw.hpp>
#include <SDL.h>
#include <graphics.hpp>
#include <window.hpp>
#include <sdl_graphics.hpp>

#include <iostream>

namespace waifuengine
{
namespace graphics
{
namespace debug
{
  class debug_line
  {
  public:
    debug_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a) : x1_(x1), x2_(x2), y1_(y1), y2_(y2), r_(r), g_(g), b_(b), a_(a) {}

    ~debug_line() {}

    void draw() const
    {
      // TODO: make API independent
      SDL_SetRenderDrawColor(waifuengine::graphics::get_window()->data()->get_renderer(), r_, g_, b_, a_);
      SDL_RenderDrawLine(waifuengine::graphics::get_window()->data()->get_renderer(), x1_, y1_, x2_, y2_);
      SDL_SetRenderDrawColor(waifuengine::graphics::get_window()->data()->get_renderer(), default_r, default_g, default_b, default_a);
    }

  private:
    int x1_;
    int x2_;
    int y1_;
    int y2_;
    int r_;
    int g_;
    int b_;
    int a_;

    static int const default_r;
    static int const default_g;
    static int const default_b;
    static int const default_a;
  };

  int const debug_line::default_r = 0xF5;
  int const debug_line::default_g = 0x42;
  int const debug_line::default_b = 0xE3;
  int const debug_line::default_a = 0xFF;

  static std::vector<debug_line> lines;

  void add_debug_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
  {
    lines.push_back(debug_line(x1, y1, x2, y2, r, g, b, a));
  }

  void draw_debug()
  {
    for(debug_line const& l : lines)
    {
      l.draw();
    }
    lines.clear();
  }
}
} // namespace graphics
} // namespace waifuengine