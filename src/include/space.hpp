/******************************************************************************/
/*!
\file   space.hpp
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

#ifndef _WAIFU_SPACE_H_
#define _WAIFU_SPACE_H_

#include <memory>
#include <object.hpp>
#include <unordered_map>
#include <wstr.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        using obj_map = std::unordered_map<::WaifuEngine::str, std::shared_ptr<object>>;

        class space
        {
        private:
            obj_map objects_;
            WaifuEngine::str name_;

        public:
            space(WaifuEngine::str name);
            ~space();

            void update(float dt);
            void draw();

            std::shared_ptr<object> add_object(WaifuEngine::str name);
            void remove_object(WaifuEngine::str name);

            obj_map const& get_objmap();
        };
    }
}

#endif // !_WAIFU_SPACE_H_
