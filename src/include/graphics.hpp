#ifndef _WE_GRAPHICS_HPP_
#define _WE_GRAPHICS_HPP_

#include "window_manager.hpp"

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
  }
}

#endif