/******************************************************************************/
/*!
\file   spacemanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    The space manager class contains and manages spaces.

*/
/******************************************************************************/

#ifndef _W_SPACE_MANAGER_HPP_
#define _W_SPACE_MANAGER_HPP_

#include <memory>
#include <string>
#include <unordered_map>

namespace waifuengine
{
    namespace object_management
    {
        class space;

        class space_manager
        {
        private:
            std::unordered_map<std::string, std::shared_ptr<space>> spaces_;

        public:
            space_manager();
            ~space_manager();

            std::shared_ptr<space> add_space(std::string n);
            void remove_space(std::string n);
            std::shared_ptr<space> get_space(std::string n);

            void update(float dt);
            void draw() const;

            std::size_t spaces() const;
            std::size_t objects() const;
            std::size_t components() const;

            void clear();
            void remove_object(std::string n);
        };
    }
}

#endif // !_W_SPACE_MANAGER_HPP_