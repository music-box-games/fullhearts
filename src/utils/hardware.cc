/******************************************************************************/
/*!
\file   hardware.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Utils related to hardware installed in the computer.

*/
/******************************************************************************/

#include <sstream>
#include <unordered_map>
#include <cstring>

#include <hardware.hpp>
#include <log.hpp>
#include "data_conversions.hpp"

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#endif // WINDOWS

namespace we = ::waifuengine;

namespace waifuengine
{
namespace utils
{
namespace hardware
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
    cpu.arch = "UNIMPLEMENTED";
    cpu.type = "UNIMPLEMENTED";
    cpu.cores = 0;
#ifdef WINDOWS
    static std::unordered_map<int, std::pair<std::string, std::string>> architectures{
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

    ss << a << ": " << architectures[a].first << " (" << architectures[a].second << ')';
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
    for (i = 0x80000000; i <= nexids; ++i)
    {
        __cpuid(info, i);
        if (i == 0x80000002)
        {
            std::memcpy(brandstring, info, sizeof(info));
        }
        else if (i == 0x80000003)
        {
            std::memcpy(brandstring + 16, info, sizeof(info));
        }
        else if (i == 0x80000004)
        {
            std::memcpy(brandstring + 32, info, sizeof(info));
        }
    }
    cpu.type = brandstring;
    ss.str("");

    ss << cpu;
    waifuengine::log::trace(ss.str());
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

std::ostream &operator<<(std::ostream &os, cpu_info const &cpu)
{
    os << "CPU Type: " << cpu.type << '\n'
       << "CPU Architecture: " << cpu.arch << '\n'
       << "CPU Cores: " << cpu.cores << '\n';
    return os;
}

std::ostream &operator<<(std::ostream &os, gpu_info const &gpu)
{
    os << "GPU Make: " << gpu.make << '\n'
       << "GPU Model: " << gpu.make << '\n';
    return os;
}

std::ostream &operator<<(std::ostream &os, hardware_info const &hwi)
{
    os << hwi.cpu << '\n'
       << hwi.gpu << '\n'
       << "Total memory: " << hwi.memory << "GB\n";
    return os;
}

hardware_info const get_hardware_info()
{
    if (hwcache) return hwcached_info; // TODO: hmm
    hardware_info hi;
    hi.cpu = (cpucache) ? cpucached_info : get_cpu_info();
    hi.gpu = (gpucache) ? gpucached_info : get_gpu_info();
    hi.memory = total_ram(); // TODO: cache
    return hi;
}

hardware_info::operator std::string() const
{
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

std::string hardware_info::str() const
{
  return std::string(*this);
}

int get_cpu_core_count()
{
    return get_hardware_info().cpu.cores;
}

unsigned long double total_ram()
{
#ifdef WINDOWS
    unsigned long long ram;
    // this is kb
    BOOL result = GetPhysicallyInstalledSystemMemory(&ram);
    if(result)
    {
      return ::we::utils::byte_conversion<utils::byte_table::kilobyte, utils::byte_table::gigabyte>(unsigned long double(ram));
    }
    else
    {
        // TODO: some kind of error handling here with GetLastError()
        return 0;
    }
#endif //WINDOWS

    return 0;
}

#ifdef DEBUG
void print_cpu_info()
{
    get_cpu_info();
}
#endif // DEBUG
} // namespace hardware

} // namespace utils
} // namespace waifuengine