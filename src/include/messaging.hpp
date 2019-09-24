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

#include <unordered_map>
#include <set>
#include <functional>
#include <wstr.hpp>
#include <system.hpp>

#define MSGNAME(x) static constexpr const char * NAME = #x

namespace WaifuEngine
{
    namespace messaging
    {
        class message
        {

        };

        class inputevent : public message
        {
            typedef std::function<void(WaifuEngine::str)> tcallback;
        };

        class messenger : public ::WaifuEngine::system<messenger>
        {
        private:
            static messenger * instance_;
            messenger() {};

            void dispatch_message();

            std::unordered_map<WaifuEngine::str, std::set<std::function<void(void)>>> events_;
        public:
            SYS_NAME(messenger);
            static messenger * get_instance();
            virtual ~messenger();

            virtual void update(float) override {}
            virtual void draw() const override {}
        };
    }
}

#endif // !_WAIFU_MESSAGING_H_
