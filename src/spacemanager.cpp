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
        std::shared_ptr<spacemanager> spacemanager::instance_ = nullptr;

        spacemanager::spacemanager() : system<spacemanager>(), spaces_(space_map()){}

        std::shared_ptr<spacemanager>& spacemanager::get_instance()
        {
            if(instance_ == nullptr)
            {
                instance_.reset(new spacemanager());
            }
            return instance_;
        }

        spacemanager::~spacemanager()
        {
            
        }

        void spacemanager::update(float) {}

        void spacemanager::draw() const {}

        space_ptr& spacemanager::add_space(WaifuEngine::str name)
        {
            spaces_.insert(name, std::make_shared<space>(name));
        }
    }
}