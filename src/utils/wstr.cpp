#include <wstr.hpp>

namespace WaifuEngine
{
    namespace io
    {
        bool string_contains(WaifuEngine::str s, WaifuEngine::str find)
        {
            return s.find(find) != WaifuEngine::str::npos;
        }
    }
}