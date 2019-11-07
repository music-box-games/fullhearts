#include <sstream>
#include <unordered_map>
#include <cstring>

#include <hardware.hpp>
#include <log.hpp>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#endif // WINDOWS

namespace waifuengine
{
    namespace utils
    {
        static bool hwcache = false;
        static bool cpucache = false;
        static bool gpucache = false;

        static hardware_info hwcached_info;
        static cpu_info cpucached_info;
        static gpu_info gpucached_info;

        static cpu_info get_cpu_info()
        {
			cpu_info cpu;
#ifdef WINDOWS
            static std::unordered_map<int, std::pair<std::string, std::string>> architectures
            {
                {9, {"PROCESSOR_ARCHITECTURE_AMD64", "x64 (AMD or Intel)"}},
                {5, {"PROCESSOR_ARCHITECTURE_ARM", "ARM"}},
                {12, {"PROCESSOR_ARCHITECTURE_ARM64", "ARM64"}},
                {6, {"PROCESSOR_ARCHITECTURE_IA64", "Intel Itanium-based"}},
                {0, {"PROCESSOR_ARCHITECTURE_INTEL", "x86"}},
                {0xffff, {"PROCESSOR_ARCHITECTURE_UNKNOWN", "Unknown architecture"}},
            };

            std::stringstream ss;
            // get info about processor
            // architecture
            SYSTEM_INFO si;
            GetSystemInfo(&si);
            auto a = si.wProcessorArchitecture;

            ss << a << ": " << architectures[a].first << " (" << architectures[a].second << ')' ;
            cpu.arch = ss.str();
            ss.str("");

            // number of processors
            ss << si.dwNumberOfProcessors;
            ss >> cpu.cores;
            ss.str("");

            // cpu type string
            int info[4] = {-1};
            unsigned nexids = 0, i = 0;
            char brandstring[0x40];
            // extended id info
            __cpuid(info, 0x80000000);
            nexids = info[0];
            for(i = 0x80000000; i <= nexids; ++i)
            {
                __cpuid(info, i);
                if(i == 0x80000002) { std::memcpy(brandstring, info, sizeof(info)); }
                else if(i == 0x80000003) { std::memcpy(brandstring + 16, info, sizeof(info)); }
                else if(i == 0x80000004) { std::memcpy(brandstring + 32, info, sizeof(info)); }
            }
            cpu.type = brandstring; 
            ss.str("");

            waifuengine::log::trace(std::string(cpu));
#endif // WINDOWS
            cpucache = true;
            cpucached_info = cpu;
            return cpu;
        }

        static gpu_info get_gpu_info()
        {
            gpu_info gpu;
            gpu.make = "UNIMPL";
            gpu.model = "UNIMPL";
            gpu.discrete = true;
            
            gpucache = true;
            gpucached_info = gpu;
            return gpu;
        }

        cpu_info::operator std::string()
        {
            std::stringstream ss;
            ss << "CPU Type: " << type << '\n';
            ss << "Architecture: " << arch << '\n';
            ss << "Cores: " << cores << '\n';


            return ss.str();
        }

        gpu_info::operator std::string()
        {
            std::stringstream ss;
            ss << "Make: " << make << '\n';
            ss << "Model: " << model << '\n';
            return ss.str();
        }

        hardware_info::operator std::string()
        {
            std::stringstream ss;
            ss << "\nCPU:\n";
            ss << std::string(cpu);
            ss << "\nGPU:\n";
            ss << std::string(gpu);

            return ss.str();
        }

        hardware_info const get_hardware_info()
        {
            if(hwcache) return hwcached_info;
            hardware_info hi;
            hi.cpu = (cpucache) ? cpucached_info : get_cpu_info();
            hi.gpu = (gpucache) ? gpucached_info : get_gpu_info();
            return hi;
        }

#ifdef DEBUG
		void print_cpu_info()
		{
			get_cpu_info();
		}
#endif // DEBUG

    }
}