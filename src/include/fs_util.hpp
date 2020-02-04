/******************************************************************************/
/*!
\file   fs_util.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Utilities related to filesystem.

*/
/******************************************************************************/

#ifndef _WE_FS_UTIL_HPP_
#define _WE_FS_UTIL_HPP_

#include <filesystem.hpp>

namespace waifuengine
{
  namespace utils
  {
    fs::path get_path_relative_to_exe(std::string find);
    std::string get_exe_path();
  }
}

#endif // !_WE_FS_UTILS_HPP_