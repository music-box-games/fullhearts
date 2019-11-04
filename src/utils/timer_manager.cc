#include <timer_manager.hpp>

namespace waifuengine
{
    namespace utils
    {
        namespace sc = std::chrono;

        timer_manager::timer_manager()
        {

        }

        timer_manager::~timer_manager()
        {

        }

        void timer_manager::add_timer(std::string name, trigger_timer * timer)
        {
            timers_[name] = std::shared_ptr<trigger_timer>(timer);
        }

        void timer_manager::remove_timer(std::string name)
        {
            timers_.erase(name);
        }

        std::shared_ptr<trigger_timer> timer_manager::emplace_timer(std::string name, bool repeat)
        {
            timers_[name] = std::shared_ptr<trigger_timer>(new trigger_timer(repeat));
            return timers_[name];
        }

        std::shared_ptr<trigger_timer> timer_manager::emplace_timer(std::string name, bool repeat, sc::milliseconds limit)
        {
            timers_[name] = std::shared_ptr<trigger_timer>(new trigger_timer(repeat, limit));
            return timers_[name];
        }

        std::shared_ptr<trigger_timer> timer_manager::emplace_timer(std::string name, bool repeat, sc::milliseconds limit, std::function<void()> trigger)
        {
            timers_[name] = std::shared_ptr<trigger_timer>(new trigger_timer(repeat, limit, trigger));
            return timers_[name];
        }

        void timer_manager::update()
        {
            static int const count = 0; // counter to only purge so often
            static int const purge_limit = 100; // 

            static auto const f = [](std::pair<std::string, std::shared_ptr<trigger_timer>> t) -> void {
                t.second->update();
            };

            if(count == purge_limit)
            {
                purge();
                count = 0;
            }
            ++count;
        }

        void timer_manager::draw()
        {
            
        }
    }
}
