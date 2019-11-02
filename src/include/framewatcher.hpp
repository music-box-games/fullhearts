#ifndef _W_FRAME_WATCHER_HPP_
#define _W_FRAME_WATCHER_HPP_

#include <cstddef>
#include <queue>
#include <chrono>

namespace waifuengine
{
    namespace core
    {
        class frame_watcher
        {
        private:
            typedef std::chrono::steady_clock::time_point::rep frame_val_t;

            std::size_t target_;
            std::size_t const retain_ = 100; // how many samples to retain
            std::deque<frame_val_t> history_; // history of frame times
            std::chrono::steady_clock::time_point last_hit_;

        public:
            frame_watcher(std::size_t target = 30);
            ~frame_watcher();

            void hit();
            std::size_t fps() const;
        };
    }
}

#endif // !_W_FRAME_WATCHER_HPP_
