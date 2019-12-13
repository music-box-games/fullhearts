#include <physics.hpp>
#include <hardware.hpp>

namespace waifuengine
{
    namespace components
    {
        bool physics2::model_calculated = false;

        physics2::physics2() : component<physics2>()
        {
            if(!model_calculated) best_model();
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

        void physics2::best_model()
        {
            auto hw = ::waifuengine::utils::hardware::get_hardware_info();
            if(hw.gpu.discrete)
            {
                model_ = calculation_model::gpu;                
            }
            else
            {
                model_ = calculation_model::cpu;
            }
            model_calculated = true;
        }
    }
}
