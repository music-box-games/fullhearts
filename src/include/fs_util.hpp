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

#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No filesystem support"
#endif

namespace waifuengine
{
  namespace utils
  {
    fs::path get_path_relative_to_exe(std::string find);
  }
}

#endif // !_WE_FS_UTILS_HPP_