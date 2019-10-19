#ifndef _W_UTILS_H_
#define _W_UTILS_H_

#include <string>

namespace WaifuEngine
{
    namespace utils
    {
        namespace string
        {
            std::string wtomb(std::wstring& tc);
            std::wstring mbtow(std::string& tc);
        }
    }
}

#endif // !_W_UTILS_H_
