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

namespace waifuengine
{
namespace core
{
namespace settings
{
void load()
{

}

bool pedantic_debug = false;
bool mt_messaging = false;
bool fullscreen = false;

int window_width = 800;
int window_height = 600;

} // namespace settings
} // namespace core
} // namespace waifuengine