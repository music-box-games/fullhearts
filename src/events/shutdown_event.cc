#include "shutdown_event.hpp"

namespace waifuengine
{
  namespace events
  {
    shutdown_event::shutdown_event() : event(std::string(NAME)) {}
    shutdown_event::~shutdown_event() {}
  }
}