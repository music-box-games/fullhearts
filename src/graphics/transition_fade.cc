#include "transition_fade.hpp"
#include "gameobject.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "scenes.hpp"
#include "sprite.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      object_management::objectptr build_transition_fade()
      {
        auto scn = we::scenes::current_scene();
        auto sp_manager = scn->get_manager();
        auto tr_sp = sp_manager->get_space("Transition Space");
        auto obj = tr_sp->add_object_t<fade>("fade_transition");
        return obj;
      }

      void fade::time_up()
      {
        auto scn = we::scenes::current_scene();
        auto sp_manager = scn->get_manager();
        auto tr_sp = sp_manager->get_space("Transition Space");
        tr_sp->mark_object_for_removal(name_);
      }

      fade::fade(std::string const& name, int ms) : object_management::gameobject(name)
      {
        we::utils::trigger_timer * tmr = new we::utils::trigger_timer(false, std::chrono::milliseconds(ms), std::bind(&fade::time_up, this));
        tmr->start();
        we::utils::timers::add_timer("splashscreen fade transition timer", tmr);
      }
    }
  }
}