/******************************************************************************/
/*!
\file   log.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Handles logging.

*/
/******************************************************************************/

#include <iostream>
#include <unordered_map>

#include <log.hpp>
#include <settings.hpp>

namespace waifuengine
{
    namespace log
    {
        static std::unordered_map<trace_level, std::string> levels
        {
            {trace_level::pedantic, "[PED-TRACE] "},
            {trace_level::trace, "[TRACE] "},
            {trace_level::debug, "[DEBUG] "},
            {trace_level::errors, "[ERROR] "},
            {trace_level::warnings, "[WARNING] "},
        };

        static trace_level tlevel;

        namespace impl
        {
            void error_helper(std::string message, std::string file, int line)
            {
                std::stringstream ss;
                ss << '[' << file << ':' << line << "] " << message;
                waifuengine::log::error(ss.str());
            }

            void warning_helper(std::string message, std::string file, int line)
            {
                std::stringstream ss;
                ss << '[' << file << ':' << line << "] " << message;
                ::waifuengine::log::warning(ss.str());
            }
        }

        void init(trace_level l)
        {
            tlevel = l;
        }

        void shutdown()
        {

        }

        void level(trace_level l)
        {
            tlevel = l;
        }

        trace_level level()
        {
            return tlevel;
        }

        void log(std::string message, trace_level level)
        {
            if(level >= tlevel)
            {
#ifdef DEBUG
                std::cout << levels[level] << message << '\n';
                if(level == trace_level::errors) { std::cerr << levels[level] << message << '\n';}
#endif // DEBUG
            }
        }

        void pedantic(std::string message)
        {
            if(settings::pedantic_debug)
            {
                log(message, trace_level::pedantic);
            }
        }

        void trace(std::string message)
        {
            log(message, trace_level::trace);
        }

        void debug(std::string message)
        {
            log(message, trace_level::debug);
        }

        void error(std::string message)
        {
            log(message, trace_level::errors);
        }

        void warning(std::string message)
        {
            log(message, trace_level::warnings);
        }
    }
}
