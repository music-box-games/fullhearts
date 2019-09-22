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

#include "system.hpp"

namespace WaifuEngine
{
    namespace threads
    {
        using thread = boost::thread;

        using task = std::function<void()>;
        class threadpool : public system<threadpool>
        {
        private:

            static threadpool * instance_;

            std::vector<thread> pool_;

            threadpool();

            void join_done_impl(std::vector<thread>& p);
            void join_done(std::vector<thread>& p);
            void join_done();

            void try_join_done_impl(std::vector<thread>& p);
            void try_join_done(std::vector<thread>& p);
            void try_join_done();
        public:  
            SYS_NAME(threadpool);

            ~threadpool();

            static threadpool * get_instance();

            void update(float);

            void draw() {} // TODO: draw on-screen (or somewhere) some sort of usage data on threads

            void add_task(task t);

            void await_task(task t);

            void await_tasks(std::tuple<task> ts);

        };
    }
}

#endif