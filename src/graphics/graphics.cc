#include "graphics.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace impl
    {
      std::shared_ptr<window_manager> winmanager = nullptr;
    }

    void init(int width, int height, std::string title)
    {
      impl::winmanager = std::shared_ptr<window_manager>(new window_manager());
      impl::winmanager->add_window(width, height, title);
      core::debug::init_imgui();
    }

    void shutdown()
    {
      core::debug::shutdown_imgui();
      impl::winmanager.reset();
    }

    void draw()
    {
    }

    void display()
    {
      impl::winmanager->display_all();
    }

    void clear()
    {
      impl::winmanager->clear_all();
    }

    std::weak_ptr<window_manager> get_window_manager()
    {
      return impl::winmanager;
    }
  }
}