/******************************************************************************/
/*!
\file   trace.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    Handles trace messaging

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <trace.hpp>

namespace WaifuEngine
{
    namespace trace
    {
        namespace _impl
        {
            std::deque<WaifuEngine::str> logged_msgs = std::deque<WaifuEngine::str>();

            std::ofstream log;

            WaifuEngine::ofstream& get_log_file()
            {
                if(!log.is_open())
                {
                    log.open(WaifuEngine::str(LOGFILE));
                }
                return log;
            }
        }
    }
}