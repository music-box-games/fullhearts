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
#include <vector>

namespace WaifuEngine
{
    namespace object_management
    {
        using comp_map = std::unordered_map<WaifuEngine::str, std::shared_ptr<WaifuEngine::components::impl::_waifu_component_base>>;

        class object
        {
        private:
            WaifuEngine::str name_;

            comp_map components_;

        public:
            object(WaifuEngine::str name) : name_(name), components_(comp_map()) {}
            ~object() {}

            void update(float dt)
            {
                std::for_each(components_.begin(), components_.end(), [&dt](auto c) -> void {
                    c.second->update(dt);
                });
            }
            void draw() const
            {
                std::for_each(components_.begin(), components_.end(), [](auto c) -> void {
                    c.second->draw();
                });
            }

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
                components_.insert(sname, std::make_shared<_CompType>(sname));
                return components_[sname];
            }

            template<typename _CompType>
            std::shared_ptr<_CompType> get_component()
            {
                for(auto c : components_)
                {
                    if(c.first.HAS(tostr(_CompType)))
                    {
                        return c.second;
                    }
                }

                return std::shared_ptr<_CompType>(nullptr);
            }

            std::shared_ptr<WaifuEngine::components::impl::_waifu_component_base> get_component(WaifuEngine::str name)
            {
                for(auto c : components_)
                {
                    if(c.first == name)
                    {
                        return c.second;
                    }
                }
                return std::shared_ptr<::WaifuEngine::components::impl::_waifu_component_base>(nullptr);
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
                std::for_each(components_.begin(), components_.end(), [&rcount, &keys](auto c) -> void {
                    if(wio::string_contains(c.first, _CompType::NAME))
                    {
                        ++rcount;
                        keys.push_back(c.first);
                    }
                });
                std::for_each(keys.begin(), keys.end(), [this](WaifuEngine::str s) -> void {
                    components_.erase(s);
                });
                return rcount;
            }
        };
    }
}

#endif // _WAIFU_GAMEOBJ_H_