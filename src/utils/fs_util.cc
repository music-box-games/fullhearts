/******************************************************************************/
/*!
\file   fs_util.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Filesystem utilities.

*/
/******************************************************************************/

#include <boost/tokenizer.hpp>

#include <fs_util.hpp>
#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    std::filesystem::path get_path_relative_to_exe(std::string find)
    {
      if(std::filesystem::exists(std::filesystem::current_path().string() + find))
      {
        return std::filesystem::path(std::filesystem::current_path().string() + find);
      }

      boost::char_separator<char> delim("/");
      boost::tokenizer<boost::char_separator<char>> tok(find, delim);

      {
        std::stringstream ss;
        ss << "Could not find " << find << " relative to cwd (" << std::filesystem::current_path() << ')';
        we::log::warning(ss.str());
      }
      return std::filesystem::path("ERROR VALUE");
    }
  }
}