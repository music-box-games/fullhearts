/******************************************************************************/
/*!
\file   space.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    Class declaration for the Space class. A space is a container of game objects
    and handles the creation, updating, and destruction of game objects.

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <space.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        space::space(WaifuEngine::str name) : objects_(obj_map()), name_(name) {}

        space::~space() {}

        void space::update(float dt)
        {
            std::for_each(objects_.begin(), objects_.end(), [&dt](auto o) -> void {
                o.second->update(dt);
            });
        }

        void space::draw()
        {
            std::for_each(objects_.begin(), objects_.end(), [](auto o) -> void {
                o.second->draw();
            });
        }

        std::shared_ptr<object> space::add_object(WaifuEngine::str n)
        {
            int gcount = 1;
            auto sname = n;
            while(objects_.count(sname))
            {
                ::WaifuEngine::strstream ss;
                ss << gcount;
                sname = n + ss.str();
                ++gcount;
            }
            return objects_[sname];
        }

        void space::remove_object(WaifuEngine::str n)
        {
            objects_.erase(n);
        }
    }
}
