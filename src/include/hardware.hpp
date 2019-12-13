#ifndef _W_HARDWARE_HPP_
#define _W_HARDWARE_HPP_

#include <string>
#include <ostream>

namespace waifuengine
{
    namespace utils
    {
        namespace hardware
        {
            struct cpu_info
            {
                std::string arch;
                std::string type;
			    int cores;

                operator std::string();
                friend std::ostream& operator<<(std::ostream& os, cpu_info const& cpu);
            };

            struct gpu_info
            {
                std::string make;
                std::string model;
                bool discrete;

                operator std::string();
                friend std::ostream& operator<<(std::ostream& os , gpu_info const& gpu);
            };

            struct hardware_info
            {
                cpu_info cpu;
                gpu_info gpu;
                unsigned long long memory;

                operator std::string();
                friend std::ostream& operator<<(std::ostream& os, hardware_info const& hwi);
            };

            hardware_info const get_hardware_info();

            unsigned long long total_ram();
		
#ifdef DEBUG
		    void print_cpu_info();
#endif // DEBUG
        }
	}
}

#endif // !_W_HARDWARE_HPP_
