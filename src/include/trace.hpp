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

#define log(x) _impl::_impl_trace_log_func(x)
#define warning(x) _impl::_impl_trace_warning_func(x, __LINE__, __FILE__)
#define error(x) _impl::_impl_trace_error_func(x, __LINE__, __FILE__)

namespace WaifuEngine
{
    namespace trace
    {

    }
}

#endif // !_WAIFU_TRACE_H_
