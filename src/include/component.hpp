#ifndef _W_COMPONENT_HPP_
#define _W_COMPONENT_HPP_

#include <string>
#include <string_view>

#define COMPONENT_NAME(x) static constexpr const char * NAME = #x

namespace waifuengine
{
    namespace components
    {
        namespace _impl
        {
            class _base_component
            {
            public:
                std::string name;

                _base_component(std::string n);
                virtual ~_base_component();

                virtual void update(float dt) = 0;
                virtual void draw() const = 0;

                operator std::string() { return name; }
            };
        }

        template<typename _Derive>
        class component : public _impl::_base_component
        {
        public:
            component() : _impl::_base_component(_Derive::NAME) {}
            virtual ~component() {}

            virtual void update(float dt) = 0;
            virtual void draw() const = 0;
        };
    }
}

#endif // !_W_COMPONENT_HPP_