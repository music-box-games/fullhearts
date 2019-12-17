#include <sstream>

#include <engine.hpp>
#include <framewatcher.hpp>
#include <log.hpp>
#include <graphics.hpp>
#include <scenemanager.hpp>
#include <draw_test_scene.hpp>

#ifdef DEBUG
#include <hardware.hpp>
#endif // DEBUG

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
            waifuengine::log::init(waifuengine::log::trace_level::trace);
            waifuengine::graphics::init();
            waifuengine::scenes::init();
            running = true;
        }

        engine::~engine()
        {
            waifuengine::scenes::shutdown();
            waifuengine::graphics::opengl::shutdown();
            waifuengine::log::shutdown();
        }

        void engine::update()
        {
            static frame_watcher fw;
            fw.hit();
            // update things
            ::waifuengine::scenes::update(fw.frame_time());
            ::waifuengine::graphics::opengl::update(fw.frame_time());
        }

        void engine::draw() const
        {
            // draw things
            ::waifuengine::scenes::draw();
            ::waifuengine::graphics::opengl::draw();
        }

        void engine::load_initial_scene()
        {
            we::log::trace("Loading inital scene");
            ::waifuengine::scenes::load<::waifuengine::scenes::draw_test_scene>();
        }
    }
}
