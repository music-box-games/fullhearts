#ifndef _W_STRUTILS_H_
#define _W_STRUTILS_H_

#include <string>

namespace WaifuEngine
{
    namespace utils
    {
        namespace string
        {
            char * wtomb(const char * tc);
            std::string wtomb(std::wstring& tc);
            std::string wtomb(std::wstring&& tc);

            wchar_t * mbtow(const wchar_t * tc);
            std::wstring mbtow(std::string& tc);
            std::wstring mbtow(std::string&& tc);

            
        }
    }
}

#endif // !_W_STRUTILS_H_
