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

namespace we = ::waifuengine;
//namespace wef = we::factory;

namespace waifuengine
{
  namespace scenes
  {
    static void on_quit_click()
    {
      we::core::engine::shutdown();
    }

    sceneptr build_scene_mainmenu()
    {
      auto scn = blank_scene("Main Menu");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto bg_obj = graphics::background::add_background("mainmenu_bg", "School entrance");


      return scn;
    }
  } // namespace scenes
} // namespace waifuengine
