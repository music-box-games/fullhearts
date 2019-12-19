/******************************************************************************/
/*!
\file   events.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Event class. Events are used to pass info and notifications around the engine
  to registered listeners.

*/
/******************************************************************************/

#ifndef _WE_EVENTS_HPP_
#define _WE_EVENTS_HPP_

#include <string>
#include <string_view>

#define EVENT_NAME(x) static constexpr std::string_view NAME = #x

namespace waifuengine
{
  namespace events
  {
    class event
    {
    public:
      std::string name;

      event(std::string n);
      virtual ~event();
    };

    class cout_event : public event
    {
    public:
      EVENT_NAME(cout_event);

      cout_event();
      cout_event(std::string m);

      virtual ~cout_event();

      std::string message;

    };
  }
}

#endif // !_WE_EVENTS_HPP_