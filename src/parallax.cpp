/******************************************************************************/
/*!
\file   parallax.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/25/2019
\brief
    Parallax component for objects. Gives a parallax effect by tying transform
    to the transform of something else, i.e. the mouse.

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <parallax.hpp>
#include <object.hpp>

namespace WaifuEngine
{
    namespace components
    {
        parallax::parallax(object_management::object * parent, object_management::object * anchor) : component<parallax>(parent), anchor_(anchor) {}

        parallax::~parallax() {}

        object_management::object * parallax::anchor() { return anchor_; }
    }
}