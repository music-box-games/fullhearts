/******************************************************************************/
/*!
\file   benchmark.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Runs engine benchmarks

*/
/******************************************************************************/

#include <array>
#include <functional>
#include <iostream>
#include <algorithm>
#include <typeinfo>

#include <frozen/set.h>

#include <benchmark.hpp>
#include <timer.hpp>
#include <memory_manager.hpp>
#include <utils.hpp>
#include <log.hpp>

namespace we = ::waifuengine;

#ifdef WE_USE_STD_MEMORY
#define MEMORY_MANAGER_MODE "STD memory management"
#define MEMORY_MANAGER_CACHING ""
#define MEMORY_MANAGER_HEAP_SIZE ""
#else
#ifdef MEMMANAGE_CACHING
#define MEMORY_MANAGER_CACHING "\nMemory manager cache: on"
#else
#define MEMORY_MANAGER_CACHING "\nMemory manager cache: off"
#endif // MEMMANAGER_CACHING
#define MEMORY_MANAGER_MODE "custom memory management"
#define MEMORY_MANAGER_HEAP_SIZE "\nWith " << we::core::memory::size() << " bytes of heap."
#endif // WE_USE_STD_MEMORY

#define REPORT_BENCHMARK std::cout << "WaifuEngine benchmarks: " << __FUNCTION__ << std::endl

namespace waifuengine
{
  namespace benchmarks
  {
    template<typename T>
    static void alloc_helper_func(std::size_t count)
    {
      std::vector<T *> buffer;
      we::utils::timer timer;
      timer.start();
      for(int i = 0; i < count; ++i)
      {
        buffer.push_back(new T());
      }
      timer.stop();
      auto alloc_time = timer.time_elapsed<std::chrono::milliseconds>();
      std::cout << "Allocating " << count << " new " << typeid(T).name() << "(s) (" << count * sizeof(T) << " bytes at " << sizeof(T)
      << " bytes per object):\n";
      // dealloc
      timer.restart();
      for(int i = 0; i < count; ++i)
      {
        delete buffer[i];
      }
      timer.stop();
      auto dealloc_time = timer.time_elapsed<std::chrono::milliseconds>();
      std::cout << "Alloc time: " << alloc_time.count() << "ms.\n" << "Dealloc time: " << dealloc_time.count() << "ms." << std::endl; 
    }

    void memory_allocation_test()
    {
      // TODO: take averages of multiple runs for more accurate results
      REPORT_BENCHMARK;
      std::cout << "Using " << MEMORY_MANAGER_MODE << MEMORY_MANAGER_HEAP_SIZE << MEMORY_MANAGER_CACHING << "\n----------\n";
      static constexpr std::size_t ALLOC_COUNT = 1000000;
      alloc_helper_func<char>(ALLOC_COUNT);
      alloc_helper_func<short>(ALLOC_COUNT);
      alloc_helper_func<int>(ALLOC_COUNT);
      alloc_helper_func<float>(ALLOC_COUNT);
      alloc_helper_func<double>(ALLOC_COUNT);
    }

    static constexpr frozen::set<void(*)(), 1> tests = 
    {
      memory_allocation_test,
    };

    void run()
    {
      std::for_each(tests.begin(), tests.end(), [](void(*f)()) -> void {
        f();
      });
    }
  }
}