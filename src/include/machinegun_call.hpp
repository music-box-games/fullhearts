#ifndef _WE_MACHINEGUN_CALL_HPP_
#define _WE_MACHINEGUN_CALL_HPP_

#include <functional>
#include <string>

#include "timer_manager.hpp"

namespace waifuengine
{
  namespace utils
  {
    class machinegun_call
    {
    private:
      int length_ms;
      std::string name;
      bool running;

      float delta;

    public:
      machinegun_call() : length_ms(0), name(""), running(false), delta(0.f)
      {
      }
      ~machinegun_call()
      {
        timers::remove_timer(name);
      }

      bool update(float dt);

      void start(std::string const &n, int length_in_ms, int trigger_every_ms, std::function<void()> f);
    };

  } // namespace utils
} // namespace waifuengine

#endif