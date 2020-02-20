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
#include <graphics.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>
#include <input.hpp>
#include <utils.hpp>
#include <event_manager.hpp>
#include <input_event.hpp>
#include <timer_manager.hpp>
#include <audio.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
    namespace core
    {
        bool engine::running = false;

        std::unique_ptr<engine> build_engine() { return std::unique_ptr<engine>(new engine()); }

        void engine::input_handler(we::events::event * e)
        {
          we::input::input_event* ev = dynamic_cast<we::input::input_event *>(e);
          if (ev->type == we::input::input_type::PRESS && ev->key == we::input::keys::ESCAPE)
          {
            shutdown();
          }
        }

        void engine::shutdown()
        {
            running = false;
        }

        engine::engine()
        {
            waifuengine::log::init(waifuengine::log::trace_level::pedantic);
            waifuengine::events::init();
            waifuengine::graphics::init(1920, 1080, "test");
            waifuengine::audio::init();
            waifuengine::input::init();
            waifuengine::scenes::init();
            waifuengine::utils::timers::init();

            running = true;
        }

        engine::~engine()
        {
            waifuengine::utils::timers::shutdown();
            waifuengine::scenes::shutdown();
            waifuengine::input::shutdown();
            waifuengine::audio::shutdown();
            waifuengine::graphics::shutdown();
            waifuengine::events::shutdown();
            waifuengine::log::shutdown();
        }

        void engine::update()
        {
            // track frame rate
            static frame_watcher fw;
            fw.hit();

            // clear buffer
            we::graphics::clear();

            // update things
            we::utils::timers::update();
            we::input::update();
            ::waifuengine::scenes::update(static_cast<float>(fw.frame_time()));

            // now draw
            we::scenes::draw();

            // then render
            ::waifuengine::graphics::render();

            we::audio::update();
        }

        void engine::load_initial_scene()
        {
            we::log::trace("Loading inital scene");
            ::waifuengine::scenes::load<::waifuengine::scenes::scene_splashscreen>();
        }
    }
}
