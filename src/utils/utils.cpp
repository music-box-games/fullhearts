#include <locale>
#include <codecvt>

#include <utils.hpp>

namespace WaifuEngine
{
    namespace utils
    {
        namespace string
        {
            std::string wtomb(std::wstring& tc)
            {
                using convert_type = std::codecvt_utf8<wchar_t>;
                std::wstring_convert<convert_type, wchar_t> converter;
                return converter.from_bytes(tc);
            }

            std::wstring mbtow(std::string& tc)
            {
                return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tc);
            }
        }
    }
}