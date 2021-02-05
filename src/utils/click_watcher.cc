#include "click_watcher.hpp"
#include "event_manager.hpp"

namespace waifuengine
{
  namespace utils
  {
    click_watcher::click_watcher(std::function<void()> t, bool repeat) : trig_(t), repeat_(repeat), done_(false)
    {
      auto f = std::bind(&click_watcher::event_handler, this, std::placeholders::_1);
      events::subscribe<graphics::input::input_event>(this, f);
    }

    click_watcher::~click_watcher()
    {
      events::unsubcribe<graphics::input::input_event>(this);
    }

    void click_watcher::event_handler(events::event * e)
    {
      graphics::input::input_event * ie = dynamic_cast<graphics::input::input_event *>(ie);
      if(ie)
      {
        click_handler(ie);
      }
    }

    void click_watcher::click_handler(graphics::input::input_event * ev)
    {
      if(!done_)
      {
        if(ev->action == graphics::input::actions::mouse_button)
        {
          trig_();
          if(!repeat_)
          {
            done_ = true;
          }
        }
      }
    }

    bool click_watcher::repeating() const
    {
      return repeat_;
    }

    bool click_watcher::done() const
    {
      return done_;
    }
  }
}