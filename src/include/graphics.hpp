#ifndef _WE_GRAPHICS_HPP_
#define _WE_GRAPHICS_HPP_

#include "window_manager.hpp"
#include "font_manager.hpp"

namespace waifuengine
{
  namespace graphics
  {
    void init(int width, int height, std::string title);
    void shutdown();

    void draw();
    void clear();
    void display();

    std::weak_ptr<window_manager> get_window_manager();
    std::weak_ptr<font_manager> get_font_manager();
    std::weak_ptr<window> get_main_window();

  }
}

#endif