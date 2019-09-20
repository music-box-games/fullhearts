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

#include <array>
#include <thread>
#include <tuple>

typedef task task;

namespace WaifuEngine
{
    namespace threads
    {
        class threadpool
        {
        private:
            static threadpool * instance_;

            std::array<std::thread, 4> pool_;

            threadpool();
        public:  
            ~threadpool();

            static threadpool * get_instance();

            void add_task(task t);

            template<typename ... _types>
            std::tuple<_types ...> await_tasks()
            {
                std::array<std::thread, sizeof...(_types)> threads;
            }

        };
    }
}

#endif