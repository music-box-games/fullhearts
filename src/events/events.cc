/******************************************************************************/
/*!
\file   events.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Event class. Events are used to pass data around the engine to registered classes.

*/
/******************************************************************************/

#include <events.hpp>

namespace waifuengine
{
  namespace events
  {
    event::event(std::string n) : name(n) {}
    event::~event() {}

    cout_event::cout_event() : event(std::string(NAME)) {}
    cout_event::cout_event(std::string m) : event(std::string(NAME)), message(m) {}

    cout_event::~cout_event() {}

  }
}