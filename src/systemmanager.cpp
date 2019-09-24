/******************************************************************************/
/*!
\file   systemmanager.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <algorithm>
#include <systemmanager.hpp>

namespace WaifuEngine
{
    system_manager::system_manager() : systems_(sys_map()) {}

    system_manager::~system_manager()
    {
        std::for_each(systems_.begin(), systems_.end(), [](std::pair<str, base_system *> s) -> void {
            delete s.second;
        });
        systems_.clear();
    }

    void system_manager::update(float dt)
    {
        std::for_each(systems_.begin(), systems_.end(), [&dt](std::pair<str, base_system *> s) -> void {
            s.second->update(dt);
        });
    }

    void system_manager::draw() const
    {
        std::for_each(systems_.cbegin(), systems_.cend(), [](std::pair<str, base_system *> s) -> void {
            s.second->draw();
        });
    }

    void system_manager::remove_system(str name)
    {
        systems_.erase(name);
    }

    base_system * system_manager::get_system(str name)
    {
        try
        {
            return systems_.at(name);
        }
        catch(std::out_of_range const&)
        {
            trace::warning(WSTR("System manager doesn't contain system: ") + name);
            return nullptr;
        }
    }

    bool system_manager::has_system(str name)
    {
        return bool(systems_.count(name));
    }
}
