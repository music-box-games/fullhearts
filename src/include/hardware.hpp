#ifndef _W_HARDWARE_HPP_
#define _W_HARDWARE_HPP_

#include <string>

namespace waifuengine
{
    namespace utils
    {
        struct cpu_info
        {
            std::string arch;
            std::string type;
			int cores;

            operator std::string();
        };

        struct gpu_info
        {
            std::string make;
            std::string model;
            bool discrete;

            operator std::string();
        };

        struct hardware_info
        {
            cpu_info cpu;
            gpu_info gpu;

            operator std::string();
        };

        hardware_info const get_hardware_info();
		
#ifdef DEBUG
		void print_cpu_info();
#endif // DEBUG

	}
}

#endif // !_W_HARDWARE_HPP_
