/******************************************************************************/
/*!
\file   log.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Handles logging.

*/
/******************************************************************************/

#ifndef _W_TRACE_HPP_
#define _W_TRACE_HPP_

#include <string>
#include <sstream>


namespace waifuengine
{
    namespace log
    {
        namespace _impl
        {
            void error_helper(std::string message, std::string file, int line);

            void warning_helper(std::string message, std::string file, int line);

            void info_helper(std::string message, std::string file, int line);

            void debug_helper(std::string message, std::string file, int line);

            void trace_helper(std::string message, std::string file, int line);
            
            void glfw_error_cb(int ec, const char * desc);

        }

        enum class trace_level
        {
            pedantic,
            trace,
            debug,
            errors,
            warnings,
        };

        void init(trace_level l);
        void shutdown();

        void level(trace_level l);
        trace_level level();

        void log(std::string message, trace_level level);

        void pedantic(std::string message); // only prints when --pedantic is provided
        void trace(std::string message);
        void debug(std::string message);
        void error(std::string message);
        void warning(std::string message);
        void info(std::string message);

    } // namespace trace
} // namespace waifuengine


#define LOGERROR(x) _impl::error_helper(x, __FILE__, __LINE__)
#define LOGWARNING(x) _impl::warning_helper(x, __FILE__, __LINE__)
#define LOGINFO(x) _impl::info_helper(x, __FILE__, __LINE__)
#define LOGDEBUG(x) _impl::debug_helper(x, __FILE__, __LINE__)
#define LOGTRACE(x) _impl::trace_helper(x, __FILE__, __LINE__)

#endif // !_W_TRACE_HPP_
