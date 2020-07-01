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

    bool machinegun_call::update(float dt)
    {
      if(running)
      {
        delta += dt;
        
        if(delta >= length_ms)
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
      length_ms = length_m;
      delta = 0;
      running = true;
      trigger_timer * tmr = new trigger_timer(true, std::chrono::milliseconds(ms), f);
      tmr->start();
      timers::add_timer(name, tmr);
    }

    
  }
}