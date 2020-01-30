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

#include <gameobject.hpp>

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
            transform,
            shader,
            texture,
            sprite,
            
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
                std::weak_ptr<we::object_management::gameobject> parent;

                _base_component(std::string n, component_types t) : name(n), type(t) {}
                virtual ~_base_component() {}

                virtual void update(float dt) = 0;
                virtual void draw() const = 0;

                operator std::string() { return name; }
                bool operator<(_base_component const& rhs) { return type < rhs.type; }
            };
        }

        template<typename _Derive>
        class component : public _impl::_base_component
        {
        public:
            component() : _impl::_base_component(_Derive::NAME, _Derive::TYPE) {}
            virtual ~component() {}

            virtual void update(float dt) = 0;
            virtual void draw() const = 0;
        };
    }
}

#endif // !_W_COMPONENT_HPP_