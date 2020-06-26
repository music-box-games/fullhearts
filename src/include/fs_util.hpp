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

#include <vector>
#include <string>

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
    fs::path get_settings_save_folder();
    void build_save_folder();
    std::vector<fs::path> list_files_in_folder(fs::path path);
    std::vector<fs::path> recursive_list_files_in_folder(fs::path path);
    std::string strip_filename(fs::path path);
    std::string get_extension(fs::path path);

    void fs_init();
  }
}

#endif // !_WE_FS_UTILS_HPP_