#include "graphics.hpp"
#include "debug.hpp"
#include "font_manager.hpp"
#include "fs_util.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace impl
    {
      std::shared_ptr<window_manager> winmanager = nullptr;
      std::shared_ptr<font_manager> fontmanager = nullptr;
    }

    void init(int width, int height, std::string title)
    {
      impl::winmanager = std::shared_ptr<window_manager>(new window_manager());
      impl::winmanager->add_window(width, height, title);

      impl::fontmanager = std::shared_ptr<font_manager>(new font_manager());
      // load default fonts
      // TODO: do this better/data driven
      impl::fontmanager->load_font("playtime.ttf", std::string(utils::get_exe_path() + "\\assets\\fonts\\playtime.ttf"));
      impl::fontmanager->load_font("PlaytimeOblique.ttf", std::string(utils::get_exe_path() + "\\assets\\fonts\\PlaytimeOblique.ttf"));
      impl::fontmanager->load_font("Playtime3D.ttf", std::string(utils::get_exe_path() + "\\assets\\fonts\\PlaytimeWithHotToddies3D.ttf"));

      core::debug::init_imgui();
    }

    void shutdown()
    {
      core::debug::shutdown_imgui();
      impl::winmanager.reset();
      impl::fontmanager.reset();
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

    std::weak_ptr<font_manager> get_font_manager()
    {
      return impl::fontmanager;
    }

    std::weak_ptr<window> get_main_window()
    {
      return impl::winmanager->get_main_window();
    }
  }
}