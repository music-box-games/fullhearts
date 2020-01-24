/******************************************************************************/
/*!
\file   notify.hpp
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Different methods of sending notifications to the user

*/
/******************************************************************************/

#ifndef _WE_NOTIFY_HPP_
#define _WE_NOTIFY_HPP_

#include <string>

namespace waifuengine
{
  namespace utils
  {
    enum class notify_exit_code
    {
      OK = 0,
      YES,
      NO,
      CANCEL,
      X,
      // special
      NO_RETURN = -1,
    };

    enum class notification_type
    {
      toast, // W10 only, non blocking
      mb_ok, // blocking, with ok button
      mb_yn, // blocking, with yes and no buttons
      mb_oc, // blocking, with ok and cancel buttons
    };

    notify_exit_code notify(notification_type type, std::string title, std::string message);
  }
}

#endif // !_WE_NOTIFY_HPP_