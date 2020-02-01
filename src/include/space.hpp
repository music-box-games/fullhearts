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

namespace waifuengine
{
    namespace object_management
    {
        enum class space_order : int
        {
            BACKGROUND = 0,
            CHARACTER,
            FX,
            UI,
            TRANSITION,
            // special
            UNORDERED,
        };

        class gameobject;

        class space
        {
        private:
            std::string name_;
            space_order order_;

            std::map<std::string, std::shared_ptr<gameobject>> objects_;

        public:
            space(std::string n, space_order order = space_order::UNORDERED);
            ~space();

            std::shared_ptr<gameobject> add_object(std::string name);
            void remove_object(std::string name);
            std::shared_ptr<gameobject> get_object(std::string name);

            void update(float dt);
            void draw() const;

            std::size_t objects() const;
            std::size_t components() const;

            bool operator<(space const& rhs) const;
        };
    }
}

#endif // !_W_SPACE_HPP_
