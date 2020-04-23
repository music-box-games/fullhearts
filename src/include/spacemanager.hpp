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
#include <map>

#include <space.hpp>
#include <component.hpp>

namespace waifuengine
{
    namespace object_management
    {
        struct default_spaces
        {
            using ptrt = std::shared_ptr<space>;

            ptrt bg;
            ptrt ch;
            ptrt fx;
            ptrt ui;
            ptrt tr;
        };

        class space_manager
        {
        private:
            std::map<std::string, std::shared_ptr<space>> spaces_;

            std::map<std::string, space_order> const defaults =
            {
                {"Background Space", space_order::BACKGROUND },
                {"Character Space", space_order::CHARACTER },
                { "FX Space", space_order::FX },
                { "UI Space", space_order::UI },
                { "Transition Space", space_order::TRANSITION },
            };

            friend class boost::serialization::access;
            template<class Archive>
            void serialize(Archive& ar, unsigned int const version)
            {
                ar & spaces_;
            }

        public:
            space_manager();
            ~space_manager();

            std::shared_ptr<space> add_space(std::string n, space_order o = space_order::UNORDERED);
            void remove_space(std::string n);
            std::shared_ptr<space> get_space(std::string n);

            void update(float dt);
            void draw() const;

            std::size_t spaces() const;
            std::size_t objects() const;
            std::size_t components() const;

            void clear();
            void remove_object(std::string n);

            default_spaces build_default_spaces();

            bool operator==(space_manager const& rhs) const;
        };
    }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::object_management::space_manager);

#endif // !_W_SPACE_MANAGER_HPP_