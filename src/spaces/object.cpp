/******************************************************************************/
/*!
\file   object.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/25/2019
\brief
    basic game object

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <object.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        object::object(WaifuEngine::string_typen) : components_(comp_map()), name_(n)
        {

        }

        object::~object()
        {
            std::for_each(components_.begin(), components_.end(), [](auto c) -> void {
                delete c.second;
            });
            components_.clear();
        }

        void object::update(float dt)
        {
            std::for_each(components_.begin(), components_.end(), [&dt](auto c) -> void {
                c.second->update(dt);
            });
        }

        void object::draw()
        {
            std::for_each(components_.begin(), components_.end(), [](auto c) -> void {
                c.second->draw();
            });
        }
    }
}