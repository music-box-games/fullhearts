#include <scene_splashscreen.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <background.hpp>
#include <timer_manager.hpp>
#include <timer.hpp>
#include <engine.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace scenes
{
static void transition()
{
  we::core::engine::shutdown();
}

scene_splashscreen::scene_splashscreen() : scene(std::string(NAME))
{
  auto sp = manager.add_space("Background Space", we::object_management::space_order::BACKGROUND);
  manager.add_space("Character Space", we::object_management::space_order::CHARACTER);
  manager.add_space("FX Space", we::object_management::space_order::FX);
  manager.add_space("UI Space", we::object_management::space_order::UI);
  we::graphics::background_factory::build_background("test background", "./assets/images/test/wallpaper.bmp", sp);

  we::utils::trigger_timer * t = new we::utils::trigger_timer(false, std::chrono::milliseconds(6000), transition);
  t->start();
  we::utils::timers::add_timer("splashscreen end timer", t);
}

scene_splashscreen::~scene_splashscreen()
{
  manager.clear();
}
} // namespace scenes
} // namespace waifuengine
