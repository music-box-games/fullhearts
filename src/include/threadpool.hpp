/******************************************************************************/
/*!
\file   threadpool.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/20/2019
\brief
    Thread pool

\copyright    All content (c) 2018 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_THREADPOOL_H_
#define _WAIFU_THREADPOOL_H_

#include <vector>
#include <thread>
#include <functional>
#include <cstdarg>

#include <boost/thread.hpp>

namespace WaifuEngine
{
    namespace threads
    {
        using thread = boost::thread;

        using task = std::function<void()>;
        class threadpool
        {
        private:
            static threadpool * instance_;

            std::vector<thread> pool_;

            threadpool();
        public:  
            ~threadpool();

            static threadpool * get_instance();

            void update(float);

            void add_task(task){}

            void await_task(task t){}

            void await_tasks(task){}

        };
    }
}

#endif