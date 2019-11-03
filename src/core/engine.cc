#include <sstream>

#include <engine.hpp>
#include <framewatcher.hpp>
#include <log.hpp>

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
            running = true;
        }

        engine::~engine()
        {
        }

        void engine::update()
        {
            static frame_watcher fw;
            fw.hit();
#ifdef DEBUG
            auto f = fw.fps();
            std::stringstream ss;
            ss << "Average fps: " << f;
            waifuengine::log::trace(ss.str());
#endif // DEBUG
            // update things
        }

        void engine::draw() const
        {
            // draw things
        }
    }
}
