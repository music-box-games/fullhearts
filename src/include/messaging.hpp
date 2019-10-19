/******************************************************************************/
/*!
\file   messaging.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief
    message handler

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_MESSAGING_H_
#define _WAIFU_MESSAGING_H_

#include <unordered_map>
#include <set>
#include <system.hpp>
#include <message.hpp>
#include <threadpool.hpp>

#include <typedef.hpp>

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
            
            std::unordered_map<::WaifuEngine::string_type, std::unordered_map<void *, void *>> sync_events_;
            std::unordered_map<::WaifuEngine::string_type, std::unordered_map<void *, std::function<void(boost::any)>>> async_events_;
            
            template<typename _MsgType, typename _ClassType>
            void attach_handler(_ClassType * inst, void(_ClassType::*f)(boost::any))
            {
                sync_events_[_MsgType::NAME][inst] = f;
            }

            template<typename _MsgType, typename _ClassType>
            void attach_async_handler(_ClassType * inst, void(_ClassType::*f)(boost::any))
            {
                async_events_[_MsgType::NAME][inst] = f;
            }

            template<typename _MsgType, typename _ClassType>
            void detach_handler(_ClassType * inst)
            {
                if(sync_events_.count(_MsgType::NAME))
                {
                    if(sync_events_[_MsgType::NAME].count(inst))
                    {
                        delete sync_events_[_MsgType::NAME][inst];
                        sync_events_[_MsgType::NAME].erase(inst);
                    }
                    // if that was the last callback, then clear it out
                    if(!sync_events_.count(_MsgType::NAME))
                    {
                        sync_events_.erase(_MsgType::NAME);
                    }
                }
            }

            template<typename _MsgType, typename _ClassType>
            void detach_async_handler(_ClassType * inst)
            {
                if(async_events_.count(_MsgType::NAME))
                {
                    if(async_events_[_MsgType::NAME].count(inst))
                    {
                        delete async_events_[_MsgType::NAME][inst];
                        async_events_[_MsgType::NAME].erase(inst);
                    }
                    // if that was the last callback, then clear it out
                    if(!async_events_.count(_MsgType::NAME))
                    {
                        async_events_.erase(_MsgType::NAME);
                    }
                }
            }

        public:
            SYS_NAME(messenger);
            static messenger * get_instance();
            virtual ~messenger();

            virtual void update(float) override {}
            virtual void draw() const override {}

            template<typename _MsgType, typename _ClassType, typename _DataType>
            void attach(_ClassType * inst, void(_ClassType::*f)(boost::any))
            {
                if(std::is_pointer<_DataType>::value)
                {
                    attach_handler<_MsgType, _ClassType>(inst, f);
                }    
                else
                {
                    attach_async_handler<_MsgType, _ClassType>(inst, f);
                }
            }

            template<typename _MsgType, typename _ClassType, typename _DataType>
            void detach(_ClassType * inst)
            {
                if(!inst) return;
                if(std::is_pointer<_DataType>::value)
                {
                    detach_handler<_MsgType, _ClassType>(inst);
                }
                else
                {
                    detach_async_handler<_MsgType, _ClassType>(inst);
                }
            }

            template<typename _MsgType, typename _DataType>
            void handle(_DataType d)
            {
                if(std::is_pointer<_DataType>::value && !d) return;
                if(std::is_pointer<_DataType>::value)
                {
                    if(sync_events_.count(_MsgType::NAME))
                    {
                        std::for_each(sync_events_[_MsgType::NAME].begin(), sync_events_[_MsgType::NAME].end(), [&d](auto f) -> void
                        {
                            (*f.second)(d);
                        });
                    }
                }
                else
                {
                    if(async_events_.count(_MsgType::NAME))
                    {
                        std::for_each(async_events_[_MsgType::NAME].begin(), async_events_[_MsgType::NAME].end(), [&d](auto f) -> void
                        {
                            ::WaifuEngine::threads::threadpool::get_instance()->add_task(std::bind(f.second, d));
                        });
                    }
                }
                
            }
        };
    }
}

#endif // !_WAIFU_MESSAGING_H_
