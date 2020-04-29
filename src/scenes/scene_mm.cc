/******************************************************************************/
/*!
\file   scene_mm.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Main menu scene

*/
/******************************************************************************/

#include <scene_mm.hpp>
#include <event_manager.hpp>
#include <input.hpp>

#include <engine.hpp>

namespace we = ::waifuengine;
//namespace wef = we::factory;

namespace waifuengine
{
namespace scenes
{
  void scene_mainmenu::on_quit_click()
  {
    we::core::engine::shutdown();
  }

  void scene_mainmenu::input_handler(we::events::event *)
  {

  }

  scene_mainmenu::scene_mainmenu() : scene(std::string(NAME))
  {
    // auto sps = manager.build_default_spaces();
    // wef::background_factory::build_background("test background", "mm_bg", sps.bg);
    // wef::button_factory::build_imagebutton("test button", "blank button", "blank button hover", std::bind(&scene_mainmenu::on_quit_click, this), sps.ui);

    auto f = std::bind(&scene_mainmenu::input_handler, this, std::placeholders::_1);
    we::events::subscribe<we::graphics::input::input_event>(this, f);
  }

  scene_mainmenu::~scene_mainmenu()
  {
    manager.clear();
    we::events::unsubcribe<we::graphics::input::input_event>(this);
  }
}
} // namespace waifuengine

BOOST_CLASS_EXPORT_IMPLEMENT(we::scenes::scene_mainmenu);