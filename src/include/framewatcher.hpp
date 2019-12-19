/******************************************************************************/
/*!
\file   framewatcher.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    The framwatcher keeps track of how long a frame takes.

*/
/******************************************************************************/

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

            std::size_t target_;
            std::size_t const retain_ = 100; // how many samples to retain
            std::deque<double> history_; // history of frame times
            std::chrono::steady_clock::time_point last_hit_;

            double get_timespan_ms(std::chrono::steady_clock::time_point s, std::chrono::steady_clock::time_point e);

        public:
            typedef std::chrono::steady_clock::time_point::rep frame_val_t;
            frame_watcher(std::size_t target = 30);
            ~frame_watcher();

            void hit();
            double fps() const;
            double frame_time() const;
        };
    }
}

#endif // !_W_FRAME_WATCHER_HPP_
