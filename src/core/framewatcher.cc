#include <algorithm>

#include <framewatcher.hpp>

namespace waifuengine
{
    namespace core
    {
        frame_watcher::frame_watcher(std::size_t target) : target_(target)
        {
            last_hit_ = std::chrono::steady_clock::now(); // init last hit so that nothing weird happens
        }

        frame_watcher::~frame_watcher() {}

        void frame_watcher::hit()
        {
            auto temp = std::chrono::steady_clock::now(); // grab the current time
            history_.push_front(std::chrono::duration_cast<std::chrono::milliseconds>((temp - last_hit_)).count());
            if(history_.size() > retain_)
            {
                history_.pop_back();
            }

            last_hit_ = temp;
        }

        std::size_t frame_watcher::fps() const
        {
            std::size_t fps = 0;
            std::for_each(history_.begin(), history_.end(), [&fps](auto& t) -> void {
                fps += t;
            });
            return fps / history_.size();
        }
    }
}