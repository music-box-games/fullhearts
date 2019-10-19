#include <locale>
#include <codecvt>

#include <strutils.hpp>

namespace WaifuEngine
{
    namespace utils
    {
        namespace string
        {
            const char * wtomb(const wchar_t * tc)
            {
                throw std::logic_error("");
                return "";
            }

            std::string wtomb(std::wstring& tc)
            {
                throw std::logic_error("");
                return "";
            }

            std::string wtomb(std::wstring&& tc)
            {
                throw std::logic_error("");
                return "";
            }

            const wchar_t * mbtow(const char * tc)
            {
                throw std::logic_error("");
                return L"";
            }

            std::wstring mbtow(std::string& tc)
            {
                throw std::logic_error("");
                return L"";
            }

            std::wstring mbtow(std::string&& tc)
            {
                throw std::logic_error("");
                return L"";
            }

        }
    }
}