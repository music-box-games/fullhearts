/******************************************************************************/
/*!
\file   messaging.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <messaging.hpp>

namespace WaifuEngine
{
    namespace messaging
    {
        messenger * messenger::instance_ = nullptr;

        void messenger::dispatch_message()
        {
            // actually send out message, use thread if threadsafe
        }

        messenger * messenger::get_instance()
        {
            if(!instance_)
            {
                instance_ = new messenger();
            }
            return instance_;
        }

        messenger::~messenger()
        {
            delete instance_;
        }
    }
}