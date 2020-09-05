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
#include "scenemanager.hpp"
#include "gameobject.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "background.hpp"
#include "sprite.hpp"
#include "scenes.hpp"
#include "transitions.hpp"
#include "timer_manager.hpp"
#include "timer.hpp"
#include "button.hpp"

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
      graphics::transitions::add_transition(graphics::transitions::transition_list::fade_in, FADE_IN_LENGTH);
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
      auto bg_obj = graphics::background::add_background("mainmenu_bg", "main_menu_bg");
      
      auto start_button = ui::add_button("start button", "blank_button", "Start", {0.f, 0.0f}, {BUTTON_WIDTH_RATIO, BUTTON_HEIGHT_RATIO});
      auto load_button = ui::add_button("load button", "blank_button", "Load", {0.f, -0.1f}, {BUTTON_WIDTH_RATIO, BUTTON_HEIGHT_RATIO});
      auto options_button = ui::add_button("options button", "blank_button", "Options", {0.f, -0.2f}, {BUTTON_WIDTH_RATIO, BUTTON_HEIGHT_RATIO});
      auto exit_button = ui::add_button("exit button", "blank_button", "Exit", {0.f, -0.3f}, {BUTTON_WIDTH_RATIO, BUTTON_HEIGHT_RATIO});
      
      start_fade_in();

      return scn;
    }
  } // namespace scenes
} // namespace waifuengine
