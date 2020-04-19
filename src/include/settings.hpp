/******************************************************************************/
/*!
\file   settings.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Engine and game settings.

*/
/******************************************************************************/

#ifndef _WE_SETTINGS_HPP_
#define _WE_SETTINGS_HPP_

namespace waifuengine
{
  namespace core
  {
    namespace settings
    {
      void load();

      extern bool pedantic_debug;
      extern bool mt_messaging;
      extern bool fullscreen;

      extern int window_width;
      extern int window_height;
    }
  }
}

#endif // !_WE_SETTINGS_HPP_