#include "scene_splashscreen.hpp"
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
#include "scene_mm.hpp"

namespace we = ::waifuengine;

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

    static void start_fade_out()
    {
      graphics::transitions::add_transition(graphics::transitions::transition_list::fade_out, FADE_OUT_LENGTH);
    }

    std::shared_ptr<scene> build_splashscreen_scene()
    {
      auto scn = blank_scene("Splashscreen");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto obj = graphics::background::add_background("splashscreen_bg", "wallpaper");
   
      utils::trigger_timer * fadeout_tmr = new utils::trigger_timer(false, std::chrono::milliseconds(FADE_IN_LENGTH + 3000), start_fade_out);
      start_fade_in();
      fadeout_tmr->start();
      utils::timers::add_timer("Fade out delay timer", fadeout_tmr);
      auto sl = []() -> void { build_scene_mainmenu(); };
      utils::trigger_timer * scene_tmr = new utils::trigger_timer(false, std::chrono::milliseconds(FADE_IN_LENGTH + 3000 + FADE_OUT_LENGTH + 1500), std::bind(queue_scene, sl));
      scene_tmr->start();
      utils::timers::add_timer("Scene change delay tiemr", scene_tmr);

      return scn;
    }
  }
}