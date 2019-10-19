/******************************************************************************/
/*!
\file   spacemanager.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/23/2019
\brief
    Manager that handles creation, updating, and destruction of spaces

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <spacemanager.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        spacemanager * spacemanager::instance_ = nullptr;

        spacemanager::spacemanager() : system<spacemanager>(), spaces_(space_map()){}

        spacemanager * spacemanager::get_instance()
        {
            if(instance_ == nullptr)
            {
                instance_ = new spacemanager();
            }
            return instance_;
        }

        spacemanager::~spacemanager()
        {
            std::for_each(spaces_.begin(), spaces_.end(), [](std::pair<WaifuEngine::str, space *> s) -> void {
                delete s.second;
            });
            spaces_.clear();

            delete instance_;
        }

        void spacemanager::update(float dt)
        {
            std::for_each(spaces_.begin(), spaces_.end(), [&dt](std::pair<WaifuEngine::str, space *> s) -> void {
                s.second->update(dt);
            });
        }

        void spacemanager::draw() const
        {
            std::for_each(spaces_.cbegin(), spaces_.cend(), [](std::pair<WaifuEngine::str, space *> s) -> void {
                s.second->draw();
            });
        }

        space * spacemanager::add_space(WaifuEngine::string_typename)
        {
            spaces_.emplace(std::make_pair(name, new space(name)));
            return spaces_[name];
        }

        void spacemanager::remove_space(WaifuEngine::string_typename)
        {
            spaces_.erase(name);
        }

        space_map& spacemanager::get_spaces()
        {
            return spaces_;
        }
    }
}