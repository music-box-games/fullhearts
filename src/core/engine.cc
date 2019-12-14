#include <sstream>

#include <engine.hpp>
#include <framewatcher.hpp>
#include <log.hpp>
#include <graphics.hpp>

#ifdef DEBUG
#include <hardware.hpp>
#endif // DEBUG

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
            waifuengine::log::trace("engine init");
            waifuengine::graphics::opengl::init();
            running = true;
        }

        engine::~engine()
        {
            waifuengine::graphics::opengl::shutdown();
            waifuengine::log::shutdown();
        }

        void engine::update()
        {
            static frame_watcher fw;
            fw.hit();
            // update things
        }

        void engine::draw() const
        {
            // draw things
        }
    }
}
