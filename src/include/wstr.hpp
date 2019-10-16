
#ifndef _W_STR_HPP_
#define _W_STR_HPP_

#include <string>
#include <sstream>

namespace WaifuEngine
{
    typedef std::string str;
    typedef std::stringstream strstream;
}

#define WSTR(x) ::WaifuEngine::str(x)

#endif