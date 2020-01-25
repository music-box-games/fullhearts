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
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // WINDOWS

#include <frozen/map.h>

#include <notify.hpp>

namespace fr = ::frozen;

namespace waifuengine
{
namespace utils
{
  #ifdef WINDOWS
  static constexpr fr::map<int, notify_exit_code, 4> codemap = 
  {
    {IDOK, notify_exit_code::OK},
    {IDYES, notify_exit_code::YES},
    {IDNO, notify_exit_code::NO},
    {IDCANCEL, notify_exit_code::CANCEL},
  };
  #endif // WINDOWS

  static notify_exit_code mb_okay_notify(std::string title, std::string message)
  {
    #ifdef WINDOWS
    unsigned int mb_flags = MB_OK | MB_SETFOREGROUND;
    int ret = MessageBox(NULL, message.c_str(), title.c_str(), mb_flags); // 0 means error

    return codemap.at(ret);
    #endif // WINDOWS
  }

  notify_exit_code notify(notification_type type, std::string title, std::string message)
  {
    switch(type)
    {
    case notification_type::toast:
      return notify_exit_code::NO_RETURN;
      break; // TODO: impl this
    case notification_type::mb_ok:
      return mb_okay_notify(title, message); // remember this is blocking
      break;
    default:
      return notify_exit_code::NO_RETURN;
      break;
    }
  }
}
}

