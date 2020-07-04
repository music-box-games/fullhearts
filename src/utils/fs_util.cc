/******************************************************************************/
/*!
\file   fs_util.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Filesystem utilities.

*/
/******************************************************************************/

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <ShlObj.h>
#endif

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
      #ifdef WINDOWS
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
      #else
      return {};
      #endif
    }

    fs::path get_temp_folder()
    {
      return fs::temp_directory_path();
    }

    fs::path get_game_save_data_folder()
    {
      auto pt = get_save_data_folder_root();
      pt.append("fullhearts");
      return pt;
    }

    fs::path get_settings_save_folder()
    {
      auto pt = get_game_save_data_folder();
      //pt.append("settings");
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

    void build_object_save_folder()
    {
      auto pt = get_game_save_data_folder();
      pt.append("objects");
      if(!fs::exists(pt))
      {
        fs::create_directory(pt);
      }
    }

    void fs_init()
    {
      build_save_folder();
      build_scene_save_folder();
      build_object_save_folder();
    }

    std::vector<fs::path> list_files_in_folder(fs::path path)
    {
      std::vector<fs::path> list;
      for(auto const& f : fs::directory_iterator(path))
      {
        if (!fs::is_directory(f.path()))
        {
          list.push_back(f.path());
        }
      }
      return list;
    }

    std::vector<fs::path> recursive_list_files_in_folder(fs::path path)
    {
      std::vector<fs::path> list;
      for(auto const& f : fs::recursive_directory_iterator(path))
      {
        if(!fs::is_directory(f.path()))
        {
          list.push_back(f.path());
        }
      }
      return list;
    }

    std::string strip_filename(fs::path path)
    {
      std::string filename = path.filename().string();
      filename = filename.substr(0, filename.find_last_of('.'));
      return filename;
    }

    std::string get_extension(fs::path path)
    {
      return path.extension().string();
    }

    std::string strip_path_to_filename_and_ext(fs::path path)
    {
      std::string filepath = path.filename().string();
      return filepath.substr(filepath.find_last_of("\\") + 1);
    }

    std::string strip_path_to_filename_and_ext(std::string path)
    {
      return path.substr(path.find_last_of("\\") + 1);
    }
  }
}