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
#include <utils.hpp>
#include <event_manager.hpp>
#include <timer_manager.hpp>
#include <audio.hpp>
#include <thread_pool.hpp>
#include <graphics.hpp>
#include <debug.hpp>
#include <settings.hpp>
#include <scripting.hpp>
#include "shutdown_event.hpp"
#include "input_event.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
bool engine::running = false;

std::unique_ptr<engine> build_engine() { return std::unique_ptr<engine>(new engine()); }

void engine::input_handler(we::events::event *e)
{
  graphics::input::input_event * ie = dynamic_cast<graphics::input::input_event*>(e);
  if(ie->key == graphics::input::keys::backtick && ie->action == graphics::input::actions::release)
  {
    debug::toggle_imgui_window();
  }
}

void engine::shutdown_event_handler(we::events::event *e)
{
  shutdown();
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
  waifuengine::events::init();
  waifuengine::graphics::init(640, 480, "Full Hearts");
  waifuengine::core::thread_pool::init(); // NOTE: must init after graphics rn
  waifuengine::audio::init();
  waifuengine::scenes::init();
  waifuengine::utils::timers::init();
  waifuengine::core::debug::init_imgui();

  // register for events
  auto f = std::bind(&engine::input_handler, this, std::placeholders::_1);
  we::events::subscribe<we::graphics::input::input_event>(this, f);
  auto shutdown_handler = std::bind(&engine::shutdown_event_handler, this, std::placeholders::_1);
  we::events::subscribe<we::events::shutdown_event>(this, shutdown_handler);

  running = true;
}

engine::~engine()
{
  // unsub from events
  we::events::unsubcribe<we::graphics::input::input_event>(this);
  we::events::unsubcribe<we::events::shutdown_event>(this);

  waifuengine::utils::timers::shutdown();
  waifuengine::scenes::shutdown();
  waifuengine::audio::shutdown();
  waifuengine::core::thread_pool::shutdown();
  waifuengine::graphics::shutdown();
  waifuengine::events::shutdown();
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

  // update input
  graphics::get_window_manager().lock()->update_all();

  // update things
  we::utils::timers::update();
  ::waifuengine::scenes::update(dt);
  // audio update
  we::audio::update();

  // draw imgui
  we::core::debug::render_imgui();
  // now draw
  we::scenes::draw();


  // TODO: draw next frame in small window for debugging

  // then present on screen, this is where the frame buffers are swapped and what we've been drawing becomes
  // visible to the user
  we::core::debug::present_imgui();
  ::waifuengine::graphics::display();


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
