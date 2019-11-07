#ifndef _W_TIMER_HPP_
#define _W_TIMER_HPP_

#include <chrono>
#include <functional>

namespace waifuengine
{
    namespace utils
    {
        class timer
        {
        protected:
            std::chrono::steady_clock::time_point start_;
            std::chrono::steady_clock::time_point end_;

            bool running_;

        public:
            timer();
            ~timer();

            void start();
            void stop();
            void restart();

            template<typename _tsType>
            _tsType time_elapsed()
            {
                auto n = std::chrono::steady_clock::now();

                return std::chrono::duration_cast<_tsType>(n - start_).count();
            }
        };

        class trigger_timer : public timer
        {
        private:
            std::chrono::milliseconds limit_; // time limit to trigger on
            bool repeat_; // if the timer should repeat or just die
            std::function<void()> trigger_; // trigger to call when timer runs out

            template<typename _input>
            std::chrono::milliseconds to_ms(_input& value)
            {
                return std::chrono::duration_cast<std::chrono::milliseconds>(value);
            }

        public:
            trigger_timer(bool repeat);
            trigger_timer(bool repeat, std::chrono::milliseconds limit);
            trigger_timer(bool repeat, std::chrono::milliseconds limit, std::function<void()> trigger);
            ~trigger_timer();

            void set_limit_us(std::chrono::microseconds limit);
            void set_limit_ms(std::chrono::milliseconds limit);
            void set_limit_s(std::chrono::seconds limit);
            void set_limit_m(std::chrono::minutes limit);

            void set_trigger(std::function<void()> t);

            template<typename _fromType>
            void set_limit_t(_fromType limit)
            {
                limit_ = std::chrono::duration_cast<std::chrono::milliseconds>(limit);
            }

            void update();

            bool done() const;
        };
    }
}

#endif // !_W_TIMER_HPP_
