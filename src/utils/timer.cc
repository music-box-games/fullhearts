/******************************************************************************/
/*!
\file   timer.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Timer class. Times things.

*/
/******************************************************************************/

#include <timer.hpp>

namespace waifuengine
{
    namespace utils
    {
        namespace sc = std::chrono;

        clock::clock() : start_time(std::chrono::steady_clock::now()) {}
        clock::~clock() {}

        std::chrono::milliseconds clock::restart_ms()
        {
          auto ret = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
          start_time = std::chrono::steady_clock::now();
          return ret;
        }

        std::chrono::milliseconds clock::get_time_elapsed_ms()
        {
          return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
        }

        std::chrono::seconds clock::restart_s()
        {
          auto ret = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time);
          start_time = std::chrono::steady_clock::now();
          return ret;
        }

        std::chrono::seconds clock::get_time_elapsed_s()
        {
          return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time);
        }



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

        frame_timer::frame_timer() : timer() {start();}
        frame_timer::~frame_timer() {}

        float frame_timer::delta_time()
        {
            return static_cast<float>(time_elapsed<std::chrono::milliseconds>().count());
        }

        float frame_timer::delta_time_reset()
        {
            float dt = delta_time();
            restart();
            return dt;
        }

        trigger_timer::trigger_timer(bool repeat) : timer(), limit_(0), repeat_(repeat) {}
        trigger_timer::trigger_timer(bool repeat, sc::milliseconds limit) : timer(), limit_(limit), repeat_(repeat) {}
        trigger_timer::trigger_timer(bool repeat, sc::milliseconds limit, std::function<void()> trigger) : timer(), limit_(limit), repeat_(repeat), on_trigger_(trigger) {}
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
            on_trigger_ = t;
        }

        void trigger_timer::update()
        {
            auto tm = sc::steady_clock::now();
            if (sc::duration_cast<sc::milliseconds>(tm - start_).count() >= limit_.count())
            {
                complete();
            }
        }

        bool trigger_timer::done() const
        {
            return !repeat_ && (sc::duration_cast<sc::milliseconds>(sc::steady_clock::now() - start_).count() >= limit_.count());
        }

        void trigger_timer::complete()
        {
          if(running_)
          {
            
            on_trigger_();
            if(!repeat_) { stop(); } else { restart(); }
          }
        }
    }
}
