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

#include <dummy.hpp>
#include <serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <fs_util.hpp>

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
        class gameobject
        {
        private:         
            using component_map = std::unordered_map<std::string, std::shared_ptr<waifuengine::components::_impl::_base_component>>;

            friend class boost::serialization::access;
            component_map components_;

            std::string name_;
            std::string error_;
            std::mutex lock_;

            bool disabled_;

            void register_components_with_archive(boost::archive::text_oarchive& ar);
            void register_components_with_archive(boost::archive::text_iarchive& ar);

            template<class Archive>
            void serialize(Archive & ar, unsigned int const)
            {
                ar & components_;
                ar & name_;
            }

        public:
            gameobject(std::string n = "");
            virtual ~gameobject();

            template<class _CType>
            std::shared_ptr<_CType> add_component()
            {
                std::scoped_lock lock(lock_);
                auto ptr = std::shared_ptr<_CType>(new _CType);
                ptr->parent = this;
                components_[_CType::NAME] = ptr; // TODO: handle multiple of one component
                return ptr;
            }

            template<class _CType>
            void remove_component()
            {
              std::scoped_lock lock(lock_);

                components_.erase(_CType::NAME);
            }

            template<class _CType>
            std::shared_ptr<waifuengine::components::_impl::_base_component> get_component()
            {
                std::scoped_lock lock(lock_);

                return (components_.count(_CType::NAME)) ? components_[_CType::NAME] : nullptr;
            }

            template<class _CType>
            bool has_component() const
            {
              std::scoped_lock lock(lock_);
              return components_.count(_CType::NAME);
            }

            bool has_component(std::string name) const;

            virtual void update(float dt);
            virtual void draw() const;

            std::string const& name() const;

            std::size_t components() const 
            { 
              return components_.size(); 
            }

            bool operator==(gameobject const& rhs);

            std::string dump() const;

            std::string get_error() const;

            // disables the object
            // Set to false to re-enable
            void disable(bool set = true);

            static void save(std::shared_ptr<gameobject> obj);

            static void load(std::shared_ptr<gameobject> obj, std::string name);

            static std::unordered_map<std::string, fs::path>& get_object_list();

            static void update_object_list();
        };
        using objectptr = std::shared_ptr<gameobject>;
    }
}

#endif // !_W_GAMEOBJECT_HPP_
