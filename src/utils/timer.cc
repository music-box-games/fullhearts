
#include <timer.hpp>

namespace waifuengine
{
    namespace utils
    {
        namespace sc = std::chrono;

        timer::timer() : running_(false)
        {

        }

        timer::~timer()
        {

        }

        void timer::start()
        {
            start_ = sc::steady_clock::now();
            running_ = true;
        }

        void timer::stop()
        {
            if(running_)
            {
                end_ = sc::steady_clock::now();
                running_ = false;
            }
        }

        void timer::restart()
        {
            start();
        }

        trigger_timer::trigger_timer(bool repeat) : repeat_(repeat) {}
        trigger_timer::trigger_timer(bool repeat, sc::milliseconds limit) : repeat_(repeat), limit_(limit) {}
        trigger_timer::trigger_timer(bool repeat, sc::milliseconds limit, std::function<void()> trigger) {}
        trigger_timer::~trigger_timer() {}

        void trigger_timer::set_limit_us(sc::microseconds limit)
        {
            set_limit_t(limit);
        }

        void trigger_timer::set_limit_ms(sc::milliseconds limit)
        {
            limit_ = limit;
        }

        void trigger_timer::set_limit_s(sc::seconds limit)
        {
            set_limit_t(limit);
        }

        void trigger_timer::set_limit_m(sc::minutes limit)
        {
            set_limit_t(limit);
        }

        void trigger_timer::set_trigger(std::function<void()> t)
        {
            trigger_ = t;
        }

        void trigger_timer::update()
        {
            auto tm = sc::steady_clock::now();
            if (sc::duration_cast<sc::milliseconds>(tm - start_).count() >= limit_.count())
            {
                trigger_();
                if(!repeat_) { stop(); } else { restart(); }
            }
        }

        bool trigger_timer::done() const
        {
            return !repeat_ && (sc::duration_cast<sc::milliseconds>(sc::steady_clock::now() - start_).count() >= limit_.count());
        }
    }
}
