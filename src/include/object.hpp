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

#include <wstr.hpp>
#include <component.hpp>
#include <memory>
#include <unordered_map>
#include <algorithm>

namespace WaifuEngine
{
    namespace objects
    {
        class object
        {
        private:
            WaifuEngine::str name_;

            std::unordered_map<WaifuEngine::str, WaifuEngine::components::impl::_waifu_component_base> components_;

        public:
            object(WaifuEngine::str name);
            ~object();

            void update(float dt);
            void draw() const;

            template<typename _CompType>
            std::shared_ptr<_CompType> add_component(WaifuEngine::str name)
            {
                int cnum = 1;
                WaifuEngine::str sname = name;
                while(components_.count(sname))
                {
                    WaifuEngine::strstream ss;
                    ss << cnum;
                    sname = name + ss.str();
                }
            }

            void remove_component(WaifuEngine::str name)
            {
                if(components_.count(name))
                {
                    components_.erase(name);
                }
            }

            template<typename _CompType>
            int remove_comps_of_type()
            {
                int rcount = 0;
                std::vector<WaifuEngine::str> keys;
                std::for_each(components_.begin(), components_.end() [&rcount, &keys](auto c) -> void {
                    if(wio::string_contains(c.first, _CompType::NAME))
                    {
                        ++rcount;
                        keys.push_back(c.first);
                    }
                });
                std::for_each(keys.begin(), keys.end(), [&components_](WaifuEngine::str s) -> void {
                    components_.erase(s);
                });
                return rcount;
            }
        };
    }
}

#endif // _WAIFU_GAMEOBJ_H_