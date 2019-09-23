/******************************************************************************/
/*!
\file   wstr.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/21/2019
\brief
    typedef'd string types for easy switching between string and wstring

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_WSTR_H_
#define _WAIFU_WSTR_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string_view>

#define STRWIDE 0

#define tostr(x) #x

#if STRWIDE
namespace WaifuEngine
{
    typedef std::wstring str;
    typedef std::wstringstream strstream;
    typedef std::wostream ostr;
    typedef std::wofstream ofstream;
    typedef std::wifstream ifstream;
    typedef std::wstring_view string_view;
    namespace io {}
}
#else // STRWIDE
namespace WaifuEngine
{
    typedef std::string str;
    typedef std::stringstream strstream;
    typedef std::ostream ostr;
    typedef std::ofstream ofstream;
    typedef std::ifstream ifstream;
    typedef std::string_view string_view;
    namespace io {}
}
#endif // STRWIDE

namespace WaifuEngine
{
    namespace io
    {
        bool string_contains(::WaifuEngine::str s, ::WaifuEngine::str find);

        template<typename T>
        str type_to_string()
        {
            return tostr(T);
        }
    }
}

#define HAS(x) find(x) != WaifuEngine::str::npos

namespace wio = ::WaifuEngine::io;

#endif // !_WAIFU_STR_H_