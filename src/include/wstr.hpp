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

#define STRWIDE 0

#if STRWIDE
namespace WaifuEngine
{
    typedef std::wstring str;
    typedef std::wstringstream strstream;
    typedef std::wostream ostr;
    namespace io {}
}
#else // STRWIDE
namespace WaifuEngine
{
    typedef std::string str;
    typedef std::stringstream strstream;
    typedef std::ostream ostr;
    namespace io {}
}
#endif // STRWIDE

namespace wio = WaifuEngine::io;

#endif // !_WAIFU_STR_H_