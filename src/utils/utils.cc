/******************************************************************************/
/*!
\file   utils.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Various utilities.

*/
/******************************************************************************/

#include <fstream>

#include <boost/math/constants/constants.hpp>

#include <utils.hpp>
#include <log.hpp>


namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    std::vector<std::string> parse_file_to_vector(std::string f)
    {
      std::ifstream file(f);
      if(!file.is_open())
      {
        std::stringstream ss;
        ss << "Could not open file: " << f;
        we::log::warning(ss.str());
        return {};
      }
      std::string buffer;
      std::vector<std::string> lines;
      while(std::getline(file, buffer))
      {
        lines.push_back(buffer);
      }

      return lines;
    }

    std::string parse_file_to_string(std::string f)
    {
      auto v = parse_file_to_vector(f);
      std::stringstream ss;
      for(auto const& s : v)
      {
        ss << s << '\n';
      }

      return ss.str();
    }

    int str_to_int(std::string s)
    {
      return std::stoi(s);
    }

    float degrees_to_radians(float d)
    {
      return d * (boost::math::constants::pi<float>() / 180.0f);
    }

    float radians_to_degrees(float r)
    {
      return r * (180.0f / boost::math::constants::pi<float>());
    }
  }
}