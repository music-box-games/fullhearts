#ifndef _WE_STR_UTIL_HPP_
#define _WE_STR_UTIL_HPP_

#include <string>
#include <vector>

namespace waifuengine
{
  namespace utils
  {
    std::string wide_string_to_mb(std::wstring ws);
    std::vector<std::string> tokenize_string(std::string s, std::string delim = " ");
    constexpr unsigned int string_to_int(const char * s, int h=0)
    {
      return !s[h] ? 5381 : (string_to_int(s, h+1) * 33) ^ s[h];
    }
  }
}

#endif