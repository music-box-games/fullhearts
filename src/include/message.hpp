/******************************************************************************/
/*!
\file   message.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief
    Different types of messages

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_MESSAGE_H_
#define _WAIFU_MESSAGE_H_

#include <functional>
#include <boost/any.hpp>
#include <wstr.hpp>

#define MSGNAME(x) static constexpr const char * NAME = #x

namespace WaifuEngine
{
    namespace messaging
    {
        namespace impl
        {
            struct _base_message
            {
                WaifuEngine::str const NAME; 
            }; 
        }

        template<typename msg>
        struct message : public impl::_base_message
        {
            message() : impl::_base_message(msg::NAME) {}
        };

        struct inputevent : public message<inputevent>
        {
            typedef WaifuEngine::str _datatype;
            //typedef std::function<void(_datatype)>;

            _datatype data_;

            MSGNAME(inputevent);
        };
    }
}

#endif // !_WAIFU_MESSAGE_H_
