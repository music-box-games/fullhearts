/******************************************************************************/
/*!
\file   space.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Space class. A space contains and manages game obejcts.

*/
/******************************************************************************/

#ifndef _W_SPACE_HPP_
#define _W_SPACE_HPP_

#include <map>
#include <memory>
#include <string>
#include <set>

#include <component.hpp>
#include <gameobject.hpp>
#include <debug.hpp>

#include "graphics_primatives.hpp"

namespace waifuengine
{
    namespace object_management
    {
        enum class space_order : int
        {
            BACKGROUND = 0,
            CHARACTER,
            UNORDERED,
            FX,
            UI,
            TRANSITION,
            // special
        };

        class gameobject;

        class space
        {
        private:
            std::string name_;
            space_order order_;

            std::map<std::string, std::shared_ptr<gameobject>> objects_;
            std::set<std::string> objects_to_remove;

            friend class waifuengine::core::debug::imgui_listener;
        

        public:
            space(std::string n = "", space_order order = space_order::UNORDERED);
            ~space();

            // MUST be derived from gameobject
            template<class ObjectType, class ... Types>
            std::shared_ptr<ObjectType> add_object_t(Types ... args)
            {
              auto obj = std::shared_ptr<ObjectType>(new ObjectType(args...));
              objects_[obj->name()] = obj;
              return obj;
            }

            std::shared_ptr<gameobject> add_object(std::string name);
            void remove_object(std::string name);
            void mark_object_for_removal(std::string name);
            std::shared_ptr<gameobject> get_object(std::string name);
            bool has(std::string name);

            void update(float dt);
            void draw() const;

            std::size_t objects() const;
            std::size_t components() const;

            bool operator<(space const& rhs) const;
            bool operator==(space const& rhs) const;

            void disable_all(bool disable = true);

            std::shared_ptr<gameobject> load_object(std::string name);
        };

        using spaceptr = std::shared_ptr<space>;
    }
}


#endif // !_W_SPACE_HPP_
