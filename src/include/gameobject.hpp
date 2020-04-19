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
#include <mutex>

#include <serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_member.hpp>

namespace waifuengine
{
    namespace components
    {
        namespace _impl
        {
            class _base_component;
        }
        class serializable_component;
    }
}

namespace waifuengine
{
    namespace object_management
    {
        using serialized_map = std::unordered_map<std::string, waifuengine::components::serializable_component>;
        using unserialized_map = std::unordered_map<std::string, std::shared_ptr<waifuengine::components::_impl::_base_component>>;

        class gameobject
        {
        private:
            friend class boost::serialization::access;
            template<class _CType>
            std::shared_ptr<_CType> add_component(_CType const& c)
            {
                std::scoped_lock(lock_);
                auto ptr = std::shared_ptr<_CType>(new _CType(c));
                ptr->parent = this;
                components_[_CType::NAME] = ptr;
                return ptr;
            }           

            std::unordered_map<std::string, std::shared_ptr<waifuengine::components::_impl::_base_component>> components_;

            std::string name_;
            std::mutex lock_;

            serialized_map convert_map_to_serializable();
            void convert_serialized_map(serialized_map const& m);

            template<class Archive>
            void save(Archive& ar, const unsigned int version)
            {
                // convert components to a serializable type
                serialized_map serialized_components = convert_map_to_serializable();
            }
            template<class Archive>
            void load(Archive& ar, const unsigned int version)
            {

            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()

        public:
            gameobject(std::string n);
            ~gameobject();

            template<class _CType>
            std::shared_ptr<_CType> add_component()
            {
                std::scoped_lock(lock_);
                auto ptr = std::shared_ptr<_CType>(new _CType);
                ptr->parent = this;
                components_[_CType::NAME] = ptr; // TODO: handle multiple of one component
                return ptr;
            }

            template<class _CType>
            void remove_component()
            {
              std::scoped_lock(lock_);

                components_.erase(_CType::NAME);
            }

            template<class _CType>
            std::shared_ptr<waifuengine::components::_impl::_base_component> get_component()
            {
                std::scoped_lock(lock_);

                return (components_.count(_CType::NAME)) ? components_[_CType::NAME] : nullptr;
            }

            void update(float dt);
            void draw() const;

            std::string const& name() const;

            std::size_t components() const 
            { 
              std::scoped_lock(lock_);

              return components_.size(); 
            }

            bool operator==(gameobject const& rhs);
        };
    }
}

#endif // !_W_GAMEOBJECT_HPP_
