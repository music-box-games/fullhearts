#include <physics.hpp>

namespace waifuengine
{
    namespace components
    {
        physics2::physics2() : component<physics2>()
        {
            model_ = calculation_model::_d;
        }

        physics2::~physics2()
        {

        }

        void physics2::update(float)
        {
            // do update things
        }

        void physics2::draw() const
        {
            // draw? probably for debug stuff like forces
        }

        static void best_model()
        {
            // figure out what to do 
        }
    }
}