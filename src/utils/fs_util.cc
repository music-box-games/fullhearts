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
    fs::path get_path_relative_to_exe(std::string find)
    {
      if(fs::exists(fs::current_path().string() + find))
      {
        return fs::path(fs::current_path().string() + find);
      }

      boost::char_separator<char> delim("/");
      boost::tokenizer<boost::char_separator<char>> tok(find, delim);

      {
        std::stringstream ss;
        ss << "Could not find " << find << " relative to cwd (" << fs::current_path() << ')';
        we::log::warning(ss.str());
      }
      return fs::path("ERROR VALUE");
    }
  }
}