/******************************************************************************/
/*!
\file   event_manager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  The event_manager class handles registering and passing around events.

*/
/******************************************************************************/

#include <event_manager.hpp>
#include "shutdown_event.hpp"
namespace waifuengine
{
  namespace events
  {
    namespace impl
    {
      event_manager::event_manager() {}
      event_manager::~event_manager() {}

      event_manager * emanager = nullptr;
    }

    void init()
    {
      if(!impl::emanager) { impl::emanager = new impl::event_manager(); }
    }

    void shutdown()
    {
      delete impl::emanager;
      impl::emanager = nullptr;
    }

    void send_shutdown_event()
    {
      shutdown_event se;
      impl::emanager->handle(&se);
    }
  }
}