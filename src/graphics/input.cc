#include <input.hpp>

namespace waifuengine
{
namespace graphics
{
namespace input
{

input_event::input_event() : event(std::string(NAME)), k(key::default), a(action::default), w(window_id_type{}) {}
input_event::input_event(key k, action a, window_id_type w) : event(std::string(NAME)), k(k), a(a), w(w) {}
input_event::~input_event() {}

void process()
{
  window::process_all_input();
}

} // namespace input
} // namespace graphics
} // namespace waifuengine