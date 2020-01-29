/******************************************************************************/
/*!
\file   gameobject.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    The game object is a container that holds and manages components.

*/
/******************************************************************************/

#ifndef _W_GAMEOBJECT_HPP_
#define _W_GAMEOBJECT_HPP_

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

namespace waifuengine
{
    namespace components
    {
        namespace _impl
        {
            class _base_component;
        }
    }
}

namespace waifuengine
{
    namespace object_management
    {
        class gameobject : public std::enable_shared_from_this<gameobject>
        {
        private:
            std::unordered_map<std::string, std::shared_ptr<waifuengine::components::_impl::_base_component>> components_;

            std::string name_;

        public:
            gameobject(std::string n);
            ~gameobject();

            template<class _CType>
            std::shared_ptr<_CType> add_component()
            {
                auto ptr = std::shared_ptr<_CType>(new _CType);
                ptr->parent = std::weak_ptr<gameobject>(shared_from_this());
                components_[_CType::NAME] = ptr; // TODO: handle multiple of one component
                return ptr;
            }

            template<class _CType>
            void remove_component()
            {
                components_.erase(_CType::NAME);
            }

            template<class _CType>
            std::shared_ptr<_CType> get_component()
            {
                return (components_.count(_CType::NAME)) ? std::shared_ptr<_CType>(dynamic_cast<_CType *>(components_[_CType::NAME].get())) : nullptr;
            }

            void update(float dt);
            void draw() const;

            std::string const& name() const;

            std::size_t components() const { return components_.size(); }
        };
    }
}

#endif // !_W_GAMEOBJECT_HPP_
