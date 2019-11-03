#ifndef _W_PHYSICS_HPP_
#define _W_PHYSICS_HPP_

#include <component.hpp>

namespace waifuengine
{
    namespace components
    {
        // todo: some sort of adding forces and doing gravity and stuff, then apply it to the transform or something?
        class physics2 : public component<physics2>
        {
        public:
            enum class calculation_model
            {
                cpu = 0,
                gpu,

                // special
                count, // number of real enums in enum (?)
                _d = cpu, // default
            };

            COMPONENT_NAME(physics2);

            physics2();
            virtual ~physics2();

            virtual void update(float dt);
            virtual void draw() const;

            static void best_model();

            static calculation_model model_; // this should be serialized if possible
            static bool model_calculated;
        };

        typedef physics2 physics;
    }
}

#endif // !_W_PHYSICS_HPP_