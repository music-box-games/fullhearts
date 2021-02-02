#ifndef _WE_WINDOW_MANAGER_HPP_
#define _WE_WINDOW_MANAGER_HPP_

#include "window.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class window_manager
    {
    public:
      window_manager();
      ~window_manager();

      void update_all();
      void clear_all();
      void display_all();

      std::weak_ptr<window> get_main_window();
      std::weak_ptr<window> get_window(int index);

      std::weak_ptr<window> add_window(int width, int height, std::string title);
      void destroy_window(int index);
      void destroy_all();

    private:
      std::vector<std::shared_ptr<window>> windows;
    };
  }
}

#endif