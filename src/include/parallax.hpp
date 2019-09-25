/******************************************************************************/
/*!
\file   parallax.hpp
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

#ifndef _WAIFU_PARALLAX_H_
#define _WAIFU_PARALLAX_H_

#include <component.hpp>

namespace WaifuEngine
{
    namespace components
    {
        class parallax : public component<parallax>
        {
        private:
            object_management::object * anchor_;
        public:
            COMPONENT_NAME(parallax);

            parallax(object_management::object * parent, object_management::object * anchor);            
            virtual ~parallax();

            object_management::object * anchor();
        };
    }
}

#endif // !_WAIFU_PARALLAX_H_