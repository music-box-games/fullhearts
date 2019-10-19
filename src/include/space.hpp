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
#include <unordered_map>
#include <object.hpp>
#include <typedef.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        using obj_map = std::unordered_map<::WaifuEngine::string_type, std::shared_ptr<object>>;

        class space
        {
        private:
            obj_map objects_;
            WaifuEngine::string_type name_;

        public:
            space(WaifuEngine::string_type name);
            ~space();

            void update(float dt);
            void draw();

            std::shared_ptr<object> add_object(WaifuEngine::string_type name);
            void remove_object(WaifuEngine::string_type name);

            obj_map const& get_objmap();
        };
        typedef std::shared_ptr<space> space_ptr;
    }
}

#endif // !_WAIFU_SPACE_H_
