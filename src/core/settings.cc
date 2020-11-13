/******************************************************************************/
/*!
\file   settings.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Contains settings for game and engine

*/
/******************************************************************************/

#include <settings.hpp>
#include "utils.hpp"
#include "events.hpp"
#include "event_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{

settings::settings_change_event::settings_change_event() : we::events::event(std::string(NAME)), name(std::string()), old_value(0), new_value(0) {}
settings::settings_change_event::settings_change_event(std::string n, std::any o_value, std::any n_value) : we::events::event(std::string(NAME)), name(n), old_value(o_value), new_value(n_value) {}
void settings::settings_change_event::reset()
{
  old_value.reset();
  new_value.reset();
  name = std::string();
}

void settings::send_change_event(std::string n, std::any o_value, std::any n_value)
{
  settings_change_event e(n, o_value, n_value);
  we::events::handle<settings_change_event>(&e);
}

std::unordered_map<std::string, settings::setting_value> settings::values =
{
  {"pedantic_debug", settings::setting_value("pedantic_debug", false)},
  {"mt_messaging", settings::setting_value("mt_messaging", false)},
  {"fullscreen", settings::setting_value("fullscreen", false)},
  {"window_width", settings::setting_value("window_width", int(1280))},
  {"window_height", settings::setting_value("window_height", int(720))},
  {"frame_limit", settings::setting_value("frame_limit", std::size_t(0))},
};

void settings::save(settings const&)
{

}

void settings::load()
{

  
}

settings::setting_value::setting_value(std::string n, std::any v) : name(n), value(v) {}

} // namespace core
} // namespace waifuengine
