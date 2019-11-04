#ifndef _W_MESSAGING_HPP_
#define _W_MESSAGING_HPP_

#include <functional>
#include <unordered_map>

#include <message.hpp>

namespace waifuengine
{
    namespace messaging
    { /*
        class message_handler
        {
        private:
            std::unordered_map<std::string, std::unordered_map<void *, void *>> message_map_;       

        public:
            message_handler();
            ~message_handler();

            template<typename _tSubscriber, typename _tMessage>
            void subscribe(_tSubscriber * instance, std::function<void()> handler)
            {

            }

            template<typename _tSubscriber, typename _tMessage>
            void unsubscribe(_tSubscriber * instance)
            {

            }        
        };
        */
    }
}

#endif // !_W_MESSAGING_HPP_