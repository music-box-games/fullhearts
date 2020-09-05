/******************************************************************************/
/*!
\file   engine.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Class that represents the entire engine. Takes care of initialization and shutdown
    for all ssytems

*/
/******************************************************************************/

#include <sstream>
#include <thread>

#include <engine.hpp>
#include <framewatcher.hpp>
#include <log.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>
#include <input.hpp>
#include <utils.hpp>
#include <event_manager.hpp>
#include <timer_manager.hpp>
#include <audio.hpp>
#include <thread_pool.hpp>
#include <graphics.hpp>
#include <debug.hpp>
#include <settings.hpp>
#include <scripting.hpp>
#include "graphics_primatives.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
bool engine::running = false;

std::unique_ptr<engine> build_engine() { return std::unique_ptr<engine>(new engine()); }

void engine::input_handler(we::events::event *e)
{
  we::graphics::input::input_event *ev = dynamic_cast<we::graphics::input::input_event *>(e);
  if (ev->a == we::graphics::input::action::press && ev->k == we::graphics::input::key::escape)
  {
    shutdown();
  }
  else if (ev->a == we::graphics::input::action::press && ev->k == we::graphics::input::key::grave_accent)
  {
    we::core::debug::toggle_imgui_window();
  }
}

void engine::shutdown()
{
  running = false;
}

void engine::_unsafe_immediate_shutdown(engine* e)
{
  delete e;
}

engine::engine()
{
  waifuengine::core::scripting::init();
  waifuengine::utils::fs_init();
  waifuengine::log::init(waifuengine::log::trace_level::pedantic);
  waifuengine::core::thread_pool::init();
  waifuengine::events::init();
  waifuengine::graphics::init("Full Hearts");
  waifuengine::audio::init();
  waifuengine::scenes::init();
  waifuengine::utils::timers::init();
  waifuengine::core::debug::init_imgui();

  // register for input events
  auto f = std::bind(&engine::input_handler, this, std::placeholders::_1);
  we::events::subscribe<we::graphics::input::input_event>(this, f);

  running = true;
}

engine::~engine()
{
  waifuengine::core::debug::shutdown_imgui();
  waifuengine::utils::timers::shutdown();
  waifuengine::scenes::shutdown();
  waifuengine::audio::shutdown();
  waifuengine::graphics::shutdown();
  waifuengine::events::shutdown();
  waifuengine::core::thread_pool::shutdown();
  waifuengine::log::shutdown();
  waifuengine::core::scripting::shutdown();
}

void engine::update()
{
  // track frame rate
  static we::utils::frame_timer ft;
  float dt = ft.delta_time_reset();

  // check threads
  core::thread_pool::update();

  // clear buffer
  we::graphics::clear();

  // prep imgui
  we::core::debug::render_imgui();

  // update input
  we::graphics::input::process();

  // update things
  we::utils::timers::update();
  ::waifuengine::scenes::update(dt);

  // now draw
  we::scenes::draw();

  // draw imgui on top
  we::core::debug::present_imgui();

  // then present on screen
  ::waifuengine::graphics::present();

  // audio update
  we::audio::update();

  // apply frame limiter if applicable
  if (we::core::settings::read_t<std::size_t>("frame_limit"))
  {
    float diff = (1000.0f / static_cast<float>(we::core::settings::read_t<std::size_t>("frame_limit"))) - ft.delta_time();
    if (diff > 0)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(diff)));
    }
  }
}

void engine::load_initial_scene()
{
  we::log::LOGTRACE("Loading inital scene");
  we::scenes::scene_loader func = []() -> void { 
    //we::scenes::build_splashscreen_scene(); 
    we::scenes::build_scene_mainmenu();
    };
  we::scenes::queue_scene(func);
}
} // namespace core
} // namespace waifuengine
