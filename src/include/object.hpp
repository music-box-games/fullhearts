/******************************************************************************/
/*!
\file   object.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    basic game object

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_GAMEOBJ_H_
#define _WAIFU_GAMEOBJ_H_

#include <memory>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <mutex>

#include <typedef.hpp>
#include <component.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        using comp_map = std::unordered_map<WaifuEngine::string_type, WaifuEngine::components::impl::_waifu_component_base *>;

        // TODO:
        // This is temp currently. This impl only supports one copy of each component
        class object
        {
        private:
            comp_map components_;
            WaifuEngine::string_type name_;
            std::mutex lock_;

        public:
            object(WaifuEngine::string_type n);
            ~object();

            void update(float dt);
            void draw();

            template<typename _CompType>
            _CompType * add_component()
            {
                std::scoped_lock l(lock_);
                if(components_.count(_CompType::NAME))
                {
                    // TODO: temp
                    return nullptr;
                }
                components_.insert(_CompType::NAME, new _CompType(this));
            }

            template<typename _CompType>
            void remove_component()
            {
                std::scoped_lock l(lock_);
                if(components_.count(_CompType::NAME))
                {
                    delete components_[_CompType::NAME].second;
                    components_.erase(_CompType::NAME);
                }
            }

            template<typename _CompType>
            bool has_component()
            {
                std::scoped_lock l(lock_);
                return bool(components_.count(_CompType::NAME));
            }
        };
    }
}

#endif // _WAIFU_GAMEOBJ_H_
