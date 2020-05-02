/******************************************************************************/
/*!
\file   fs_util.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Filesystem utilities.

*/
/******************************************************************************/

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <ShlObj.h>

#include <boost/tokenizer.hpp>

#include <fs_util.hpp>
#include <log.hpp>
#include <boost/dll.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    fs::path get_path_relative_to_exe(std::string find)
    {
      if(fs::exists(fs::current_path().string() + find))
      {
        return fs::path(fs::current_path().string() + find);
      }

      boost::char_separator<char> delim("/");
      boost::tokenizer<boost::char_separator<char>> tok(find, delim);

      // TODO: recurse a bit maybe perhaps?

      {
        std::stringstream ss;
        ss << "Could not find " << find << " relative to cwd (" << fs::current_path() << ')';
        we::log::warning(ss.str());
      }
      return fs::path("ERROR VALUE");
    }

    std::string get_exe_path()
    {
      std::string p = boost::dll::program_location().string();
      p = p.substr(0, p.find_last_of("\\"));
      return p;
    }

    fs::path get_save_data_folder_root()
    {
      PWSTR p = NULL;
      auto result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &p);
      if(result != S_OK)
      {
        // ERROR
      }
      std::wstring wp(p);
      int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wp[0], (int)wp.size(), NULL, 0, NULL, NULL);
      std::string mbp(size_needed, 0);
      WideCharToMultiByte(CP_UTF8, 0, &wp[0], (int)wp.size(), &mbp[0], size_needed, NULL, NULL);

      fs::path pt(mbp);
      CoTaskMemFree(p);
      return pt;
    }

    fs::path get_temp_folder()
    {
      return std::filesystem::temp_directory_path();
    }

    fs::path get_game_save_data_folder()
    {
      auto pt = get_save_data_folder_root();
      pt.append("fullhearts");
      return pt;
    }

    void build_save_folder()
    {
      auto pt = get_game_save_data_folder();
      if(!fs::exists(pt))
      {
        fs::create_directory(pt);
      }
    }

    void build_scene_save_folder()
    {
      auto pt = get_game_save_data_folder();
      pt.append("scenes");
      if(!fs::exists(pt))
      {
        fs::create_directory(pt);
      }
    }

    void fs_init()
    {
      build_save_folder();
      build_scene_save_folder();
    }
  }
}