#include <engine.hpp>
#include <framewatcher.hpp>

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
            running = true;
        }

        engine::~engine()
        {

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
