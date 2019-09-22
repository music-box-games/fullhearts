/******************************************************************************/
/*!
\file   threadpool.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/20/2019
\brief
    Thread pool

\copyright    All content (c) 2018 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <threadpool.hpp>

namespace WaifuEngine
{
    namespace threads
    {
        threadpool * threadpool::instance_ = nullptr;

        threadpool::threadpool() {}

        threadpool::~threadpool()
        {
            std::for_each(pool_.begin(), pool_.end(), [](thread& t) -> void {
                t.interrupt();
            });
            pool_.clear();
        }

        threadpool * threadpool::get_instance()
        {
            if(instance_ == nullptr)
            {
                instance_ = new threadpool();
            }
            return instance_;
        }

        void threadpool::update(float)
        {
            try_join_done();
        }

        void threadpool::add_task(task t)
        {
            pool_.push_back(thread(t));
        }

        void threadpool::await_task(task t)
        {
            thread tk(t);
            tk.join();
        }

        void threadpool::await_tasks(std::tuple<task> ts)
        {
            std::vector<thread> thds;
            std::apply([&thds](auto&&...args) {((thds.push_back(thread(args))), ...);}, ts);
            join_done(thds);
        }

        void threadpool::join_done_impl(std::vector<thread>& p)
        {
            while(!p.empty())
            {
                int i = 0;
                std::vector<int> indices;
                std::for_each(p.begin(), p.end(), [&indices, &i](thread& t) -> void {
                    if(t.try_join_for(boost::chrono::milliseconds(10)))
                    {
                        indices.push_back(i);    
                    }
                    ++i;
                });
                std::for_each(indices.begin(), indices.end(), [&p](int ind) -> void {
                    p.erase(p.begin() + ind);
                });
            }
        }

        void threadpool::join_done(std::vector<thread>& p)
        {
            join_done_impl(p);
        }

        void threadpool::join_done()
        {
            join_done_impl(pool_);
        }

        void threadpool::try_join_done_impl(std::vector<thread>& p)
        {
            int i = 0;
            std::vector<int> indices;
            std::for_each(p.begin(), p.end(), [&indices, &i](thread& t) -> void {
                if(t.try_join_for(boost::chrono::milliseconds(10)))
                {
                    indices.push_back(i);
                }
                ++i;
            });
            std::for_each(indices.begin(), indices.end(), [&p](int ind) -> void {
                p.erase(p.begin() + ind);
            });
        }

        void threadpool::try_join_done(std::vector<thread>& p)
        {
            try_join_done_impl(p);
        }

        void threadpool::try_join_done()
        {
            try_join_done_impl(pool_);
        }
    }
}
