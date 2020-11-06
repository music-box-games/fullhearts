/******************************************************************************/
/*!
\file   hardware.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Functions and utils related to the hardware connected to the computer.

*/
/******************************************************************************/

#ifndef _W_HARDWARE_HPP_
#define _W_HARDWARE_HPP_

#include <string>
#include <ostream>
#include <cstddef>

namespace waifuengine
{
    namespace utils
    {
        namespace hardware
        {
            constexpr std::size_t BYTE = sizeof(std::byte);
            constexpr std::size_t KILOBYTE = BYTE * 1024;
            constexpr std::size_t MEGABYTE = KILOBYTE * 1024;
            constexpr std::size_t GIGABYTE = MEGABYTE * 1024;

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
                unsigned long double memory;

                operator std::string() explicit const;

                std::string str() const;

                friend std::ostream& operator<<(std::ostream& os, hardware_info const& hwi);
            };

            hardware_info const get_hardware_info();

            int get_cpu_core_count();

            unsigned long double total_ram();
		
#ifdef DEBUG
		    void print_cpu_info();
#endif // DEBUG
        }
	}
}

#endif // !_W_HARDWARE_HPP_
