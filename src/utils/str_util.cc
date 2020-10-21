#include <algorithm>
#include <random>

#include <str_util.hpp>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#endif

#include <boost/tokenizer.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    std::string wide_str_to_mb(std::wstring ws)
    {
      #ifdef WINDOWS
      int size_needed = WideCharToMultiByte(CP_UTF8, 0, &ws[0], (int)ws.size(), NULL, 0, NULL, NULL);
      std::string mbp(size_needed, 0);
      WideCharToMultiByte(CP_UTF8, 0, &ws[0], (int)ws.size(), &mbp[0], size_needed, NULL, NULL);
      return mbp;
      #else
      return "";
      #endif
    }

    std::vector<std::string> tokenize_string(std::string s, std::string delim)
    {
      boost::char_separator<char> sep(delim.c_str());
      boost::tokenizer<boost::char_separator<char>> tok(s, sep);
      std::vector<std::string> tokens;
      std::for_each(tok.begin(), tok.end(), [&tokens](auto s) -> void {
        tokens.push_back(s);
      });
      return tokens;
    }

    std::string random_str(std::size_t length)
    {
      using namespace std::string_view_literals;
      static constexpr std::string_view character_set =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"sv;

      thread_local std::mt19937 rng(std::random_device{}());
      auto distribution = std::uniform_int_distribution{{}, character_set.size() - 1};
      std::string result(length, '\0');
      std::generate_n(std::begin(result), length, [&]() {return character_set.at(distribution(rng));});
      return result;
    }
  }
}