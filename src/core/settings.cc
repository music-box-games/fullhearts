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
#include <serialization.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace settings
{

void load()
{

}
void save()
{

}

bool pedantic_debug = false;
bool mt_messaging = false;
bool fullscreen = false;

int window_width = 800;
int window_height = 600;

namespace impl
{

settings_state::settings_state(bool load_current)
{
  if(load_current)
  {
    load_current_settings();
  }
  else
  {
    pedantic_debug = false;
    mt_messaging = false;
    fullscreen = false;
    window_width = 0;
    window_height = 0;
  }
}

settings_state::~settings_state() {}

void settings_state::load_current_settings()
{
  pedantic_debug = we::core::settings::pedantic_debug;
  mt_messaging = we::core::settings::mt_messaging;
  fullscreen = we::core::settings::fullscreen;
  window_width = we::core::settings::window_width;
  window_height = we::core::settings::window_height;
}

void settings_state::apply() const
{
  we::core::settings::pedantic_debug = pedantic_debug;
  we::core::settings::mt_messaging = mt_messaging;
  we::core::settings::fullscreen = fullscreen;
  we::core::settings::window_width = window_width;
  we::core::settings::window_height = window_height;
}

bool settings_state::operator==(settings_state const& rhs) const
{
  return (pedantic_debug == rhs.pedantic_debug) &&
  (mt_messaging == rhs.mt_messaging) &&
  (fullscreen == rhs.fullscreen) &&
  (window_width == rhs.window_width) &&
  (window_height == rhs.window_height);
}

} // namespace impl
} // namespace core
} // namespace settings
} // namespace waifuengine

BOOST_CLASS_EXPORT_IMPLEMENT(waifuengine::core::settings::impl::settings_state);
