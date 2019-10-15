/******************************************************************************/
/*!
\file   beavhior.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   10/14/2019
\brief
    behavior component for game objects. This runs the core of the game, and be
    also be used as AI.

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _W_COMPONENT_H_
#define _W_COMPONENT_H_

#include <functional>

#include <component.hpp>

namespace WaifuEngine
{
    namespace components
    {
        class behavior : public component<behavior>
        {
        private:
        public:
            static auto constexpr ALWAYS_TRUE = []() -> bool { return true; };
            static auto constexpr ALWAYS_FALSE = []() -> bool { return false; };

            COMPONENT_NAME(behavior);

            behavior(object_management::object * parent);
            behavior(behavior const& other);

            virtual ~behavior();

            virtual void update(float dt);
            virtual void draw() const;

            void add_behavior(std::function<bool()> trigger, std::function<void()> action);

        };
    }
}

#endif // !_W_COMPONENT_H_