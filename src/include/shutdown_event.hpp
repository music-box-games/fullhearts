#ifndef _WE_SHUTDOWN_EVENT_HPP_
#define _WE_SHUTDOWN_EVENT_HPP_

#include "events.hpp"

namespace waifuengine
{
  namespace events
  {
    class shutdown_event : public event 
    {
    public:
      EVENT_NAME(shutdown_event);
      shutdown_event();
      virtual ~shutdown_event();
    };
  }
}

#endif