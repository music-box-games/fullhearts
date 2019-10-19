/******************************************************************************/
/*!
\file   trace.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    Handles trace messaging

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_TRACE_H_
#define _WAIFU_TRACE_H_

#include <queue>
#include <string_view>

#include <typedef.hpp>
#include <system.hpp>

#define writelog(level, message) _impl::impl_trace_log(level, message, __LINE__, __FILE__)
#define log(m) writelog(::WaifuEngine::trace::trace_level::log, m)
#define verbose(m) writelog(::WaifuEngine::trace::trace_level::verbose, m)
#define trace(m) writelog(::WaifuEngine::trace::trace_level::trace, m)

namespace WaifuEngine
{
    namespace trace
    {
        enum class trace_level
        {
            log = 0,
            verbose,
            trace,

            // special
            count,
        };

        namespace _impl
        {
            void _impl_trace_log(::WaifuEngine::trace::trace_level level, ::WaifuEngine::string_type message, decltype(__LINE__) l, decltype(__FILE__) f);
        }

        void write(trace_level lvl, ::WaifuEngine::string_type message);
    }
}

#endif // !_WAIFU_TRACE_H_
