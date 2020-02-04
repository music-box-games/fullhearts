#include <scene_splashscreen.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <factories.hpp>
#include <timer_manager.hpp>
#include <timer.hpp>
#include <engine.hpp>
#include <event_manager.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace scenes
{
static void transition()
{
  we::scenes::queue_load<scene_mainmenu>();
}

static we::utils::trigger_timer * transition_timer = nullptr;

void scene_splashscreen::input_handler(we::events::event * ievent)
{
  we::input::input_event * e = dynamic_cast<we::input::input_event *>(ievent);
  if(e->type == we::input::input_type::PRESS)
  {
    if(transition_timer)
    {
      transition_timer->complete();
    }
  }
}

scene_splashscreen::scene_splashscreen() : scene(std::string(NAME))
{
  auto sp = manager.add_space("Background Space", we::object_management::space_order::BACKGROUND);
  manager.add_space("Character Space", we::object_management::space_order::CHARACTER);
  manager.add_space("FX Space", we::object_management::space_order::FX);
  manager.add_space("UI Space", we::object_management::space_order::UI);
  manager.add_space("Transition Space", we::object_management::space_order::TRANSITION);
  we::factory::background_factory::build_background("test background", "splash screen", sp);

  transition_timer = new we::utils::trigger_timer(false, std::chrono::milliseconds(6000), transition);
  transition_timer->start();
  we::utils::timers::add_timer("splashscreen end timer", transition_timer);

  // hook input events for skipping screen
  auto f = std::bind(&scene_splashscreen::input_handler, this, std::placeholders::_1);
  we::events::subscribe<we::input::input_event>(this, f);
}

scene_splashscreen::~scene_splashscreen()
{
  we::events::unsubcribe<we::input::input_event>(this);
  manager.clear();
}
} // namespace scenes
} // namespace waifuengine
