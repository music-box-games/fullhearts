/******************************************************************************/
/*!
\file   memory_manager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Custom memory management.

*/
/******************************************************************************/

#include <new>
#include <cstdlib>
#include <cstddef>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <mutex> // scoped_lock
#include <cstring> // memset
#include <memory> // std::unique_ptr

#include <frozen/set.h>

#include <memory_manager.hpp>
#include <hardware.hpp>
#include <allocator.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace memory
{

  // TODO: change this to all be the same increments for easy lookup when alloc request isn't perfectly aligned
  // set of different data sizes
  static constexpr frozen::set<std::size_t, 47> data_sizes = 
  {
    // 4 byte increments
    4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
    52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,
    // 32 byte increments
    128, 160, 192, 224, 256, 288, 320, 352, 384,
    416, 448, 480, 512, 544, 576, 608, 634,
    // 64 byte increments
    704, 768, 832, 896, 960, 1024,
  };

  class manager
  {
  private:
    std::unordered_map<std::size_t, std::unique_ptr<allocator>> allocators;

  public:
    manager() {}
    ~manager() {}

    void init()
    {
      // TODO: build default allocator(s)
    }

    void shutdown()
    {
      allocators.clear(); // clear the allocators, which will handle cleanup themselves
    }

    void * allocate(std::size_t size)
    {
      // TODO: get proper allocator for size and pass info along
      return nullptr;
    }

    void deallocate(void * ptr, std::size_t size)
    {
      // TODO: get proper allocator for size, then call deallocation from that
    }
  };

  memory_debugger::memory_debugger(void* man)
  {
#ifdef DEBUG
    manage = static_cast<we::core::memory::manager*>(man);
#else
    manage = nullptr;
#endif // DEUBG
  }

  memory_debugger::memory_debugger(memory_debugger& other)
  {
#ifdef DEBUG
    manage = other.manage;
#else
    manage = nullptr;
#endif
  }

  memory_debugger::~memory_debugger() {}

  void * memory_debugger::alloc(std::size_t s) 
  { 
#ifdef DEBUG
    return manage->allocate(s); 
#else
    return nullptr;
#endif // DEBUG
  }

  void memory_debugger::dealloc(void * ptr, std::size_t s) 
  {
#ifdef DEBUG
    manage->deallocate(ptr, s); 
#endif // DEBUG
  }

  std::byte * memory_debugger::get_pool() 
  { 
#ifdef DEBUG
    return nullptr;
#else 
    return nullptr;
#endif
  }

  static manager man;

  memory_debugger attach_debugger()
  {
    return memory_debugger(&man);
  }

  void init(std::size_t size, allocation_policy fit)
  {
    man.init();
  }

  void shutdown()
  {
    // TODO: check for unreleased memory
    // TODO: if debug gather stats about session
    man.shutdown();
  }

}
} // namespace core
} // namespace waifuengine

#ifndef WE_USE_STD_MEMORY

void * operator new(std::size_t size)
{
}

void* operator new[](std::size_t size)
{
}

void operator delete(void * ptr, std::size_t size)
{
}

void operator delete[](void* ptr, std::size_t size)
{
}

#endif // WE_USE_STD_MEMORY

