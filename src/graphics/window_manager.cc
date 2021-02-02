#include <algorithm>

#include "window_manager.hpp"

namespace waifuengine
{
  namespace graphics
  {
    window_manager::window_manager() {}
    window_manager::~window_manager() {}

    void window_manager::update_all()
    {
      std::for_each(windows.begin(), windows.end(), [](std::shared_ptr<window> w) -> void { w->update(); });
    }

    void window_manager::clear_all()
    {
      std::for_each(windows.begin(), windows.end(), [](std::shared_ptr<window> w) -> void { w->clear(); });
    }

    void window_manager::display_all()
    {
      std::for_each(windows.begin(), windows.end(), [](std::shared_ptr<window> w) -> void { w->display(); });
    }

    std::weak_ptr<window> window_manager::get_main_window()
    {
      return get_window(0);
    }

    std::weak_ptr<window> window_manager::get_window(int index)
    {
      return windows.at(index);
    }

    std::weak_ptr<window> window_manager::add_window(int width, int height, std::string title)
    {
      windows.push_back(std::shared_ptr<window>(new window(width, height, title)));
      return get_window(windows.size() - 1); 
    }

    void window_manager::destroy_window(int index)
    {
      windows.erase(windows.begin() + index);
    }

    void window_manager::destroy_all()
    {
      windows.clear();
    }
  }
}