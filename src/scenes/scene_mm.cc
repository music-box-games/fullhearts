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

#include <engine.hpp>
#include "background.hpp"
#include "scenemanager.hpp"
#include "gameobject.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "sprite.hpp"
#include "scenes.hpp"
#include "timer_manager.hpp"
#include "timer.hpp"
#include "fs_util.hpp"

namespace we = ::waifuengine;
//namespace wef = we::factory;

namespace waifuengine
{
  namespace scenes
  {

    static constexpr int FADE_IN_LENGTH = 2000;
    static constexpr int FADE_OUT_LENGTH = 2000;

    static void start_fade_in()
    {
    }

    static void on_quit_click()
    {
      we::core::engine::shutdown();
    }

    sceneptr build_scene_mainmenu()
    {
      constexpr float BUTTON_WIDTH_RATIO = 0.15f;
      constexpr float BUTTON_HEIGHT_RATIO = 0.2f;

      auto scn = blank_scene("Main Menu");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto bgsp = sp_manager->get_space("background_space");
      std::stringstream texture_path;
      texture_path << utils::get_exe_path() << "\\assets\\images\\test\\wallpaper.png";
      auto bg_obj = bgsp->add_object_t<graphics::background>("mainmenu_bg", texture_path.str());

      start_fade_in();

      return  scn;
    }
  } // namespace scenes
} // namespace waifuengine
