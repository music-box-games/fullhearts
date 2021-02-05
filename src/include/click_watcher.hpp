#ifndef _WE_CLICK_WATCHER_HPP_
#define _WE_CLICK_WATCHER_HPP_

#include <functional>
#include "input_event.hpp"

namespace waifuengine
{
  namespace utils
  {
    class click_watcher
    {
    public:
      click_watcher(std::function<void()> trigger, bool repeat = false);
      ~click_watcher();

      bool repeating() const;
      bool done() const;

    private:
      void event_handler(events::event * e);
      void click_handler(graphics::input::input_event * e);

      std::function<void()> trig_;
      bool repeat_;
      bool done_;
    };
  }
}

#endif