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
#include <draw_test_scene.hpp>
#include <input.hpp>
#include <memory_manager.hpp>
#include <hardware.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
    namespace core
    {
        bool engine::running = false;

        std::unique_ptr<engine> build_engine() { return std::unique_ptr<engine>(new engine()); }

        void engine::shutdown()
        {
            running = false;
        }

        engine::engine()
        {
            waifuengine::log::init(waifuengine::log::trace_level::pedantic);
            waifuengine::graphics::init();
            waifuengine::input::init();
            waifuengine::scenes::init();
            running = true;
        }

        engine::~engine()
        {
            waifuengine::scenes::shutdown();
            waifuengine::input::shutdown();
            waifuengine::graphics::shutdown();
            waifuengine::log::shutdown();
        }

        void engine::update()
        {
            static frame_watcher fw;
            fw.hit();
            // clear buffer
            we::graphics::clear();

            // update things
            we::input::update();
            ::waifuengine::scenes::update(fw.frame_time());

            // now draw
            we::scenes::draw();

            // then render
            ::waifuengine::graphics::render();
        }

        void engine::load_initial_scene()
        {
            we::log::trace("Loading inital scene");
            ::waifuengine::scenes::load<::waifuengine::scenes::draw_test_scene>();
        }
    }
}
