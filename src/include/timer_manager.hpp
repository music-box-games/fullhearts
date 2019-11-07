#ifndef _W_TIMERMANAGER_HPP_
#define _W_TIMERMANAGER_HPP_

#include <unordered_map>
#include <memory>

#include <timer.hpp>

namespace waifuengine
{
    namespace utils
    {
        class timer_manager
        {
        private:
            std::unordered_map<std::string, std::shared_ptr<trigger_timer>> timers_;

            void purge();
            
        public:
            timer_manager();
            ~timer_manager();

            void add_timer(std::string name, trigger_timer * timer);
            void remove_timer(std::string name);

            std::shared_ptr<trigger_timer> emplace_timer(std::string name, bool repeat);
            std::shared_ptr<trigger_timer> emplace_timer(std::string name, bool repeat, std::chrono::milliseconds limit);
            std::shared_ptr<trigger_timer> emplace_timer(std::string name, bool repeat, std::chrono::milliseconds limit, std::function<void()> trigger);

            void update();
        };
    }
}

#endif // !_W_TIMERMANAGER_HPP_
