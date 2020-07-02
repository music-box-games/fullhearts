#include "scene_splashscreen.hpp"
#include "scenemanager.hpp"
#include "gameobject.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "background.hpp"
#include "sprite.hpp"
#include "scenes.hpp"
#include "transitions.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {

    static void start_fade_in()
    {
      graphics::transitions::add_transition(graphics::transitions::transition_list::fade_in);
    }

    static void start_fade_out()
    {
      graphics::transitions::add_transition(graphics::transitions::transition_list::fade_out);
    }

    std::shared_ptr<scene> build_splashscreen_scene()
    {
      auto scn = blank_scene("Splashscreen");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto obj = graphics::background::add_background("splashscreen_bg", "wallpaper");
      auto sprt = dynamic_cast<graphics::sprite *>(obj->get_component<graphics::sprite>().get());
      sprt->scale_to_window();   
      start_fade_in();
      return scn;
    }
  }
}