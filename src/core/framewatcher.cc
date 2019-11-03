#include <algorithm>
#include <array>
#include <functional>

#include <framewatcher.hpp>

namespace waifuengine
{
    namespace core
    {
        double frame_watcher::get_timespan_ms(std::chrono::steady_clock::time_point s, std::chrono::steady_clock::time_point e)
        {
            using tp = std::chrono::steady_clock::time_point;

            static std::array<std::function<frame_val_t(tp, tp)>, 4> const funs
            {
                [](tp s, tp e) -> frame_val_t { return std::chrono::duration_cast<std::chrono::seconds>(e - s).count(); },
                [](tp s, tp e) -> frame_val_t { return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count(); },
                [](tp s, tp e) -> frame_val_t { return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count(); },
                [](tp s, tp e) -> frame_val_t { return std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count(); }
            };
            
            auto ts = funs[0](s, e);
            if(ts != int64_t(0)) return double(ts);
            ts = funs[1](s, e);
            if(ts != int64_t(0)) return double(ts / 1000.0);
            ts = funs[2](s, e);
            if(ts != int64_t(0)) return double((ts / 1000.0) / 1000.0);
            ts = funs[3](s, e);
            if(ts != int64_t(0)) return double(((ts / 1000.0) / 1000.0) / 1000.0); // it really shouldn't have to go this far really.
            else return -1;
        }


        frame_watcher::frame_watcher(std::size_t target) : target_(target)
        {
            last_hit_ = std::chrono::steady_clock::now(); // init last hit so that nothing weird happens
        }

        frame_watcher::~frame_watcher() {}

        void frame_watcher::hit()
        {
            auto temp = std::chrono::steady_clock::now(); // grab the current time
            // calc time between frames and at it to the history deque in ms
            auto ts = get_timespan_ms(last_hit_, temp);
            last_hit_ = temp;
            history_.push_front(ts);
            if(history_.size() > retain_) { history_.pop_back(); }
        }

        double frame_watcher::fps() const
        {
            return 1 / frame_time();  // take reciprocal to get how many time-per-frames fit into 1 second
        }

        double frame_watcher::frame_time() const
        {
            double fps = 0;
            std::for_each(history_.begin(), history_.end(), [&fps](auto& t) -> void {
                fps += t;
            });
            return fps / history_.size();
        }
    }
}