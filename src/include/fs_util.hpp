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
    fs::path get_save_data_folder_root();
    fs::path get_temp_folder();
    fs::path get_game_save_data_folder();
    void build_save_folder();

    void fs_init();
  }
}

#endif // !_WE_FS_UTILS_HPP_