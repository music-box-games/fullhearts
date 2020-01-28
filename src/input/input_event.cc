#include <input_event.hpp>

namespace waifuengine
{
namespace input
{
  input_event::input_event() : events::event(std::string(NAME)), key(keys::NONE), type(input_type::NONE) {}
  input_event::input_event(keys k, input_type t) : events::event(std::string(NAME)), key(k), type(t) {}
  input_event::~input_event() {}
}
}