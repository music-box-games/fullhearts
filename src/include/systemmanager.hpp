/******************************************************************************/
/*!
\file   systemmanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief
    Manager for handles all of the engine systems.

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_SYSTEMMANANGER_H_
#define _WAIFU_SYSTEMMANAGER_H_

#include <unordered_map>
#include <system.hpp>
#include <wstr.hpp>

namespace WaifuEngine
{
    class system_manager
    {
    private:
        std::unordered_map<WaifuEngine::str, base_system *> systems_;

    public:
        system_manager();
        ~system_manager();

        void update(float dt) {}
        void draw() const {}
    };
}

#endif // !_WAIFU_SYSTEMMANAGER_H_