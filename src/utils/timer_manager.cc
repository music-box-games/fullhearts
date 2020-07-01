/******************************************************************************/
/*!
\file   timer_manager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Manager for timers, and calls the trigger when time runs out

*/
/******************************************************************************/

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

void timer_manager::add_timer(std::string name, trigger_timer *timer)
{
    timers_[name] = std::shared_ptr<trigger_timer>(timer);
}

void timer_manager::remove_timer(std::string name)
{
  if (timers_.count(name))
  {
    timers_.erase(name);
  }
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
    static int count = 0;               // counter to only purge so often
    static int const purge_limit = 100; // purge every this many cycles

    static auto const f = [](std::pair<std::string, std::shared_ptr<trigger_timer>> t) -> void {
        t.second->update();
    };

    if (count == purge_limit)
    {
        purge();
        count = 0;
    }
    for (auto &t : timers_)
    {
        f(t);
    }
    ++count;
}

void timer_manager::purge()
{
    std::vector<std::string> to_be_deleted;
    for (auto t : timers_)
    {
        if (t.second->done())
        {
        }
    }
}

namespace timers
{
namespace impl
{
static timer_manager *man = nullptr;
}

void init()
{
    if (!impl::man)
    {
        impl::man = new timer_manager();
    }
}

void shutdown()
{
    if (impl::man)
    {
        delete impl::man;
        impl::man = nullptr;
    }
}

void add_timer(std::string name, trigger_timer *timer)
{
  if (impl::man)
  {
    impl::man->add_timer(name, timer);
  }

}

void remove_timer(std::string name)
{
  if (impl::man)
  {
    impl::man->remove_timer(name);
  }
}

void update()
{
  if (impl::man)
  {
    impl::man->update();
  }

}
} // namespace timers

} // namespace utils
} // namespace waifuengine
