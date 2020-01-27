#include <input_event.hpp>

namespace waifuengine
{
namespace input
{
  input_event::input_event() : events::event(std::string(NAME)) {}
  input_event::input_event(inputs k, input_type t) : events::event(std::string(NAME)), key(k), type(t) {}
  input_event::~input_event() {}
}
}