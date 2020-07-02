
#include "machinegun_call.hpp"
#include "timer_manager.hpp"
#include "timer.hpp"
#include "log.hpp"

#include <sstream>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    machinegun_call::machinegun_call() : length_ms(0), name(""), running(false), delta(0.f)
    {

    }

    machinegun_call::~machinegun_call()
    {
      timers::remove_timer(name);
    }

    void machinegun_call::stop()
    {
      timers::remove_timer(name);
      running = false;
    }

    bool machinegun_call::update(float dt)
    {
      if(running)
      {
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() > length_ms)
        {
          timers::remove_timer(name);
          running = false;
          return false;
        }
        return true;
      }
      return false;
    }

    void machinegun_call::start(std::string const& n, int length_m, int ms, std::function<void()> f)
    {

      name = n;
      length_ms = length_m + 2000;
      delta = 0;
      running = true;
      start_time = std::chrono::system_clock::now();
      trigger_timer * tmr = new trigger_timer(true, std::chrono::milliseconds(ms), f);
      tmr->start();
      timers::add_timer(name, tmr);
    } 
  }
}