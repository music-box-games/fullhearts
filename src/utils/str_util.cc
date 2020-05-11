#include <str_util.hpp>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#endif

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
  }
}