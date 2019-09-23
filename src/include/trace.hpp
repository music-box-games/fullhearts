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

#include <wstr.hpp>
#include <queue>

#define log(x) _impl::_impl_trace_log_func(x)
#define warning(x) _impl::_impl_trace_warning_func(x, __LINE__, __FILE__)
#define error(x) _impl::_impl_trace_error_func(x, __LINE__, __FILE__)

namespace WaifuEngine
{
    namespace trace
    {
        namespace _impl
        {
            constexpr WaifuEngine::string_view LOGFILE = "./logs/log.txt";
            constexpr unsigned LOG_LENGTH = 40;
            extern std::deque<WaifuEngine::str> logged_msgs;

            WaifuEngine::ofstream& get_log_file();

            template<typename T>
            void log_to_file(T msg)
            {
                logged_msgs.push_back(msg);
                if(logged_msgs.size() > LOG_LENGTH)
                {
                    logged_msgs.pop_front();
                }

                get_log_file() << msg << '\n';
            }

            template<typename T>
            void _impl_trace_log_func(T msg)
            {
                WaifuEngine::strstream ss;
                ss << "[TRACE][LOG] " << msg;
                log_to_file(ss.str());
#ifdef _DEBUG
#if STRWIDE
                std::wcout << L"[TRACE][LOG] " << msg << std::endl;
#else // STRWIDE
                std::cout << "[TRACE][LOG] " << msg << std::endl;
#endif // STRWIDE
#endif // _DEBUG
            }

            template<typename T>
            void _impl_trace_warning_func(T msg, int l, const char * f)
            {
                WaifuEngine::strstream ss;
                ss << "[TRACE][WARNING][" << f << ':' << l << "] " << msg;
                log_to_file(ss.str());
#ifdef _DEBUG
#if STRWIDE
                std::wcout << L"[TRACE][WARNING][" << f << ':' << l << "] " << msg << std::endl;
#else // STRWIDE
                std::cout << L"[TRACE][WARNING][" << f << ':' << l << "] " << msg << std::endl;
#endif // STRWIDE
#endif // _DEBUG
            }

            template<typename T>
            void _impl_trace_error_func(T msg, int l, const char * f)
            {
                WaifuEngine::strstream ss;
                ss << "[TRACE][ERROR][" << f << ':' << l << "] " << msg;
                log_to_file(ss.str());
#ifdef _DEBUG
#if STRWIDE
                std::wcerr << L"[TRACE][ERROR][" << f << ':' << l << "] " << msg << std::endl;
#else // STRWIDE
                std::cerr << "[TRACE][ERROR][" << f << ':' << l << "] " << msg << std::endl;
#endif // STRWIDE
#endif // _DEBUG
            }
        }
    }
}

#endif // !_WAIFU_TRACE_H_
