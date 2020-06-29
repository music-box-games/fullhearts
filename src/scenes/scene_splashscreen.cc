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

    std::shared_ptr<scene> build_splashscreen_scene()
    {
      auto scn = blank_scene("Splashscreen");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      auto obj = graphics::background::add_background("splashscreen_bg", "wallpaper");
      auto sprt = dynamic_cast<graphics::sprite *>(obj->get_component<graphics::sprite>().get());
      sprt->scale(glm::vec2(2.0f, 2.0f));
      graphics::transitions::add_transition(graphics::transitions::transition_list::fade);
      
      return scn;
    }
  }
}