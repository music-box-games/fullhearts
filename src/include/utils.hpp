/******************************************************************************/
/*!
\file   utils.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Various utility functions.

*/
/******************************************************************************/

#ifndef _WE_UTLIS_HPP_
#define _WE_UTILS_HPP_

#include <vector>
#include <string>

#include <fs_util.hpp>
#include <args.hpp>
#include <bitmanip.hpp>
#include <hardware.hpp>
#include <timer_manager.hpp>
#include <timer.hpp>

#define WE_UTIL_STRINGIFY(x) #x

namespace waifuengine
{
  namespace utils
  {
    std::vector<std::string> parse_file_to_vector(std::string f);
    std::string parse_file_to_string(std::string f);

    template<typename T>
    std::string to_string()
    {
      return WE_UTIL_STRINGIFY(T);
    }
  }
}

#endif // !_WE_UTILS_HPP_