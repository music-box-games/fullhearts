/******************************************************************************/
/*!
\file   component.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    Component base class

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_COMPONENT_H_
#define _WAIFU_COMPONENT_H_

#define COMPONENT_NAME(x) static constexpr const char * NAME = #x

#include <wstr.hpp>

namespace WaifuEngine
{
    namespace components
    {
        namespace impl
        {
            class _waifu_component_base
            {
            private:
            public:
                WaifuEngine::str NAME;

                _waifu_component_base(WaifuEngine::str n) : NAME(n) {}
                virtual ~_waifu_component_base() {}

                virtual void update(float dt) = 0;
                virtual void draw() const = 0;
                
            };
        }

        template<typename _BASE>
        class component : public impl::_waifu_component_base
        {
        private:
        public:
            component() : impl::_waifu_component_base(_BASE::NAME) {}
            virtual ~component() {}

            virtual void update(float dt) = 0;
            virtual void draw() const = 0;
            
        };

        class example_component : public component<example_component>
        {
        private:
        public:
            COMPONENT_NAME(example_component);

            example_component() : component<example_component>() { /* ... example here */ }
            virtual ~example_component() { /* ... shutdown here */ }

            virtual void update(float) { /* update component here */ }
            virtual void draw() const { /* draw component here */ }
        };
    }
}

#endif // !_WAIFU_COMPONENT_H_
