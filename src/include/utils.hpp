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
#include <type_traits>

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

    template<typename T>
    constexpr auto to_underlying(T obj) noexcept
    {
      return static_cast<std::underlying_type<T>>(obj);
    }
  }
}

#endif // !_WE_UTILS_HPP_