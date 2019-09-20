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

#include "include/threadpool.hpp"

namespace WaifuEngine
{
    namespace threads
    {
        threadpool * threadpool::instance_ = nullptr;

        threadpool::threadpool() {}

        threadpool::~threadpool() {}

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
            
        }
    }
}