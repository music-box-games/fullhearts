#include <scene_mm.hpp>
#include <factories.hpp>
#include <event_manager.hpp>
#include <input_event.hpp>

#include <engine.hpp>

namespace we = ::waifuengine;
namespace wef = we::factory;

namespace waifuengine
{
namespace scenes
{
  void scene_mainmenu::input_handler(we::events::event * e)
  {
    // cast event to right type
    we::input::input_event * ie = dynamic_cast<we::input::input_event *>(e);
    if(ie->type == we::input::input_type::PRESS)
    {
      we::core::engine::shutdown();
    }
  }

  scene_mainmenu::scene_mainmenu() : scene(std::string(NAME))
  {
    auto sps = manager.build_default_spaces();
    wef::background_factory::build_background("test background", "./bin/assets/images/test/wallpaper.png", sps.bg);
    // TODO: temp

    auto f = std::bind(&scene_mainmenu::input_handler, this, std::placeholders::_1);
    we::events::subscribe<we::input::input_event>(this, f);

  }

  scene_mainmenu::~scene_mainmenu()
  {
    manager.clear();
    we::events::unsubcribe<we::input::input_event>(this);
  }
}
} // namespace waifuengine