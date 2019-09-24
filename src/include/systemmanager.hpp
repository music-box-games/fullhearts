/******************************************************************************/
/*!
\file   systemmanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_SYSTEMMANAGER_H_
#define _WAIFU_SYSTEMMANAGER_H_

#include <unordered_map>
#include <system.hpp>
#include <wstr.hpp>
#include <trace.hpp>

namespace WaifuEngine
{
    typedef std::unordered_map<str, base_system *> sys_map;

    class system_manager
    {
    private:
        std::unordered_map<str, base_system *> systems_;
    public:
        system_manager();
        ~system_manager();

        void update(float dt);
        void draw() const;

        template<typename _SysType>
        base_system * add_system()
        {
            systems_.emplace(std::make_pair(_SysType::NAME, new _SysType()));
        }

        template<typename _SysType>
        void remove_system()
        {
            systems_.erase(_SysType::NAME);
        }

        void remove_system(str name);

        template<typename _SysType>
        _SysType * get_system()
        {
            try
            {
                return systems_.at(_SysType::NAME);
            }
            catch(std::out_of_range const&)
            {
                trace::warning(WSTR("System manager doesn't contain system: ") + _SysType::NAME);
                return nullptr;
            }
        }

        base_system * get_system(str name);

        template<typename _SysType>
        bool has_system()
        {
            return bool(systems_.count(_SysType::NAME));
        }

        bool has_system(str name);
    };
}

#endif // !_WAIFU_SYSTEMMANAGER_H_