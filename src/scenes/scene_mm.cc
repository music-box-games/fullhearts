/******************************************************************************/
/*!
\file   scene_mm.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Main menu scene

*/
/******************************************************************************/

#include <vector>

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
#include "button.hpp"
#include "vfx.hpp"
#include "click_watcher.hpp"
#include "slidefx.hpp"

namespace we = ::waifuengine;
//namespace wef = we::factory;

namespace waifuengine
{
  namespace scenes
  {

    static constexpr int FADE_IN_LENGTH = 2000;
    static constexpr int FADE_OUT_LENGTH = 2000;

    namespace impl
    {
      std::vector<utils::click_watcher> cwatchers;
    }

    static void on_quit_click()
    {
      impl::cwatchers.clear();
      we::core::engine::shutdown();
    }

    sceneptr build_scene_mainmenu()
    {
      constexpr float BUTTON_WIDTH_RATIO = 0.15f;
      constexpr float BUTTON_HEIGHT_RATIO = 0.2f;

      auto scn = blank_scene("Main Menu");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto bgsp = sp_manager->get_space("Background Space");
      auto uisp = sp_manager->get_space("UI Space");
      auto trsp = sp_manager->get_space("Transition Space");

      std::stringstream bg_texture_path;
      bg_texture_path << utils::get_exe_path() << "\\assets\\images\\test\\wallpaper.png";
      auto bg_obj = bgsp->add_object_t<graphics::background>("mainmenu_bg", bg_texture_path.str());

      auto start_obj = uisp->add_object_t<ui::text_button>("start_button", std::optional<fs::path>(),"Start");
      start_obj->set_font("playtime.ttf");
      start_obj->set_color(graphics::colors::color(0,0,0,255));
      start_obj->set_translation(glm::vec2(672.f, 845.f));
      std::function<glm::vec2(glm::vec2, float)> start_obj_slide_func = [=start_obj](glm::vec2 pos, float total_elapsed) -> glm::vec2
      {
        // i hate math
        
      };
      start_obj->add_component_v<graphics::slidefx>();

      auto load_obj = uisp->add_object_t<ui::text_button>("load_button", std::optional<fs::path>(), "Load");
      load_obj->set_font("playtime.ttf");
      load_obj->set_color(graphics::colors::color(0,0,0,255));
      load_obj->set_translation(glm::vec2(821.f, 845.f));
      load_obj->add_component_v<graphics::slidefx>();
      
      auto opt_obj = uisp->add_object_t<ui::text_button>("options_button", std::optional<fs::path>(), "Options");
      opt_obj->set_font("playtime.ttf");
      opt_obj->set_color(graphics::colors::color(0,0,0,255));
      opt_obj->set_translation(glm::vec2(973.f, 845.f));
      opt_obj->add_component_v<graphics::slidefx>();

      auto ebtn_obj = uisp->add_object_t<ui::text_button>("exit_button", std::optional<fs::path>(), "Exit");
      ebtn_obj->set_font("playtime.ttf");
      ebtn_obj->set_color(graphics::colors::color(0,0,0,255));
      ebtn_obj->set_translation(glm::vec2(1147.f, 845.f));
      ebtn_obj->add_component_v<graphics::slidefx>();

      auto fdin_obj = trsp->add_object_t<graphics::vfx::fade>("mm_fade_in", 255, 0, std::chrono::milliseconds(3000));
      fdin_obj->start();

      //impl::cwatchers.push_back(utils::click_watcher([&trsp]() -> void {trsp->mark_object_for_removal("mm_fade_in");}));

      return  scn;
    }
  } // namespace scenes
} // namespace waifuengine
