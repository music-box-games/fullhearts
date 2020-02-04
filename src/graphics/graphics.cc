/******************************************************************************/
/*!
\file   graphics.cc   
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Graphics namespaces. Handles initialization and shutdown of graphics systems,
  as well as handling different graphics APIs

*/
/******************************************************************************/

#include <iostream>

#include <graphics.hpp>
#include <log.hpp>
#include <return_values.hpp>
#include <log.hpp>
#include <shader.hpp>
#include <utils.hpp>
#include <engine.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <window.hpp>
#include <debug_draw.hpp>
#include <assets.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
class graphics_manager
{
private:
  // TODO: SUPPORT MULTIPLE WINDOWS
  std::shared_ptr<we::graphics::window> window;

public:
  graphics_manager(unsigned width, unsigned height, std::string title)
  {
    window = std::shared_ptr<we::graphics::window>(new we::graphics::window(width, height, title));
  }

  ~graphics_manager()
  {
  }

  void clear()
  {
    we::log::pedantic("graphics_manager: clear");
    window->clear();
  }

  void render()
  {
    we::log::pedantic("graphics_manager: render");
    //#ifdef DEBUG
    we::graphics::debug::draw_debug();
    //#endif
    window->render();
  }

  std::shared_ptr<we::graphics::window> get_window()
  {
    return window;
  }
};

static graphics_manager * gman = nullptr;

void init(unsigned width, unsigned height, std::string title)
{
  we::log::trace("graphics: init");
  gman = new graphics_manager(width, height, title);
  we::core::assets::init();
  std::string path = we::utils::get_exe_path();
  path.append("\\data\\images.txt");
  we::core::image_assets::load_images(path);
  path = we::utils::get_exe_path();
  path.append("\\data\\fonts.txt");
  we::core::font_assets::load_fonts(path);
}

void clear()
{
  we::log::pedantic("graphics: clear");
  gman->clear();
}

void render()
{
  we::log::pedantic("graphics: render");
  gman->render();
}

void shutdown()
{
  we::log::trace("graphics: shutdown");
  we::core::assets::shutdown();
  delete gman;
  gman = nullptr;
}

std::shared_ptr<window> get_window()
{
  return gman->get_window();
}

} // namespace graphics
} // namespace waifuengine
