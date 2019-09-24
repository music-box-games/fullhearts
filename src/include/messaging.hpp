/******************************************************************************/
/*!
\file   messaging.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_MESSAGING_H_
#define _WAIFU_MESSAGING_H_

#include <wstr.hpp>
#include <system.hpp>

#define MSGNAME(x) static constexpr const char * NAME = #x

namespace WaifuEngine
{
    namespace messaging
    {
        class messenger : public ::WaifuEngine::system<messenger>
        {
        private:
            static messenger * instance_;
            messenger() {};

            void dispatch_message();
        public:
            SYS_NAME(messenger);
            static messenger * get_instance();
            virtual ~messenger();

            virtual void update(float dt) override {}
            virtual void draw() const override {}

        };

        
    }
}

#endif // !_WAIFU_MESSAGING_H_
