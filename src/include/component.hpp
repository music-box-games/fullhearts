/******************************************************************************/
/*!
\file   component.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Component base classes. Components are where all the game magic happens.

*/
/******************************************************************************/

#ifndef _W_COMPONENT_HPP_
#define _W_COMPONENT_HPP_

#include <string>
#include <string_view>
#include <typeinfo>
#include <typeindex>

#include <gameobject.hpp>
#include <serialization.hpp>

#define COMPONENT_NAME(x) static constexpr const char * NAME = #x
#define COMPONENT_TYPE(x) static constexpr ::waifuengine::components::component_types TYPE = ::waifuengine::components::component_types::x

namespace we = ::waifuengine;

namespace waifuengine
{
    namespace components
    {
        enum class component_types
        {
            physics2,
            collider,
            box_collider,
            button_collider,
            transform,
            shader,
            texture,
            sprite,
            textsprite,
            
            // special ones
            basic_shape,
            basic_triangle,
            dummy,
        };

        namespace _impl
        {
            class _base_component
            {
            public:
                std::string name;
                component_types type;
                we::object_management::gameobject * parent;

                _base_component(std::string n, component_types t) : name(n), type(t), parent(nullptr) {}
                virtual ~_base_component() {}

                virtual void update(float dt) = 0;
                virtual void draw() const = 0;

                operator std::string() { return name; }
                bool operator<(_base_component const& rhs) { return type < rhs.type; }
                
                virtual void operator=(_base_component const& rhs) = 0;
                virtual bool operator==(_base_component const& rhs) = 0;

            private:
                friend class boost::serialization::access;
                template<class Archive>
                void serialize(Archive& ar, unsigned int const version)
                {
                    ar & name;
                    ar & type;
                }
            };
            BOOST_SERIALIZATION_ASSUME_ABSTRACT(_base_component)
        }

        template<typename _Derive>
        class component : public _impl::_base_component
        {
        public:
            component() : _impl::_base_component(_Derive::NAME, _Derive::TYPE) {}
            virtual ~component() {}

            virtual void update(float dt) {}
            virtual void draw() const {}
            virtual void operator=(_base_component const& rhs)
            {
                name = rhs.name;
                type = rhs.type;
            }
            virtual bool operator==(_base_component const& rhs)
            {
                return (name == rhs.name) && (type == rhs.type);
            }
        private:
            friend class boost::serialization::access;
            template<class Archive>
            void serialize(Archive& ar, unsigned int const version)
            {
                ar & boost::serialization::base_object<_impl::_base_component>(*this);
            }
        };
    }
}

#endif // !_W_COMPONENT_HPP_