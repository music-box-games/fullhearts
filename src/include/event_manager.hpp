/******************************************************************************/
/*!
\file   event_manager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Event manager class that handles passing events off to registered listeners.

*/
/******************************************************************************/

#ifndef _WE_EVENT_MANAGER_HPP_
#define _WE_EVENT_MANAGER_HPP_

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>

#include <events.hpp>

namespace waifuengine
{
  namespace events
  {
    namespace impl {
    class event_manager
    {
    public:
      using event_callback = std::function<void(event *)>;

    private:
      using event_map = std::unordered_map<std::string, std::unordered_map<void *, event_callback>>;
      event_map events_;

    public:
      event_manager();
      ~event_manager();

      template<typename Event>
      void subscribe(void * instance, event_callback f)
      {
        std::string ename(Event::NAME);
        // check for event entry, and create if not present
        if(!events_.count(ename))
        {
          events_[ename] = {};
        }
        auto& emap = events_[ename];
        // check if an event has already been registered
        if(!emap.count(instance))
        {
          emap[instance] = {};
        }
        emap[instance] = f;
      }

      template<typename Event>
      void unsubscribe(void * instance)
      {
        std::string ename(Event::NAME);
        if(events_.count(ename))
        {
          if(events_[ename].count(instance))
          {
            //delete events_[ename][instance].first;
            events_[ename].erase(instance);
          }
        }
      }

      template<typename Event>
      void handle(Event * e)
      {
        std::string ename(Event::NAME);
        if(events_.count(ename))
        {
          auto& eset = events_[ename];
          for(auto& p : eset)
          {
            (p.second)(e);
          }
        }
      }
    };

    extern event_manager * emanager;

    }

    void init();
    void shutdown();

    template<typename Event>
    void handle(Event * e)
    {
      impl::emanager->handle(e);
    }

    template<typename Event>
    void subscribe(void * instance, impl::event_manager::event_callback f)
    {
      impl::emanager->subscribe<Event>(instance, f);
    }

    template<typename Event>
    void unsubcribe(void * instance)
    {
      impl::emanager->unsubscribe<Event>(instance);
    }

  }
}

#endif // !_WE_EVENT_MANAGER_HPP_
