/******************************************************************************/
/*!
\file   notify.cc
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Different methods of sending notifications to the user

*/
/******************************************************************************/

#ifdef WINDOWS
#include <winuser.h>
#endif // WINDOWS

#include <notify.hpp>

namespace waifuengine
{
namespace utils
{
  static notify_exit_code mb_okay_notify(std::string title, std::string message)
  {
    uint mb_flags = MB_OK | MB_SETFOREGROUND;
    int ret = MessageBox(NULL, message, title, mb_flags);
  }

  notify_exit_code notify(notification_type type, std::string title, std::string message)
  {
    switch(type)
    {
    case notification_type::toast:
      break; // TODO: impl this
    case notification_type::mb_ok:
      return mb_okay_notify(title, message); // remember this is blocking
      break;
    default:
      break;
    }
  }
}
}

