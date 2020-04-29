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

namespace we = ::waifuengine;

namespace waifuengine
{
    namespace core
    {
        bool engine::running = false;

        std::unique_ptr<engine> build_engine() { return std::unique_ptr<engine>(new engine()); }

        void engine::input_handler(we::events::event * e)
        {
          we::graphics::input::input_event* ev = dynamic_cast<we::graphics::input::input_event *>(e);
          if (ev->a == we::graphics::input::action::press && ev->k == we::graphics::input::key::escape)
          {
            shutdown();
          }
          else if(ev->a == we::graphics::input::action::press && ev->k == we::graphics::input::key::grave_accent)
          {
            we::core::debug::toggle_imgui_window();
          }
        }

        void engine::shutdown()
        {
            running = false;
        }

        engine::engine()
        {
            waifuengine::log::init(waifuengine::log::trace_level::pedantic);
            waifuengine::core::thread_pool::init();
            waifuengine::events::init();
            waifuengine::graphics::init("test");
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
        }

        void engine::update()
        {
            // track frame rate
            static frame_watcher fw;
            fw.hit();

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
            ::waifuengine::scenes::update(static_cast<float>(fw.frame_time()));

            // now draw
            we::scenes::draw();

            // draw imgui on top
            we::core::debug::present_imgui();

            // then present on screen
            ::waifuengine::graphics::present();

            we::audio::update();
        }

        void engine::load_initial_scene()
        {
            we::log::trace("Loading inital scene");
            ::waifuengine::scenes::load<::waifuengine::scenes::scene_splashscreen>();
        }
    }
}
