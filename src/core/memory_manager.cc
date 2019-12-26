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

#include <memory_manager.hpp>
#include <hardware.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace memory
{

  class manager
  {
  private:
    std::byte * pool;
    std::size_t pool_size;

    allocation_policy fit;

    std::size_t allocations;
    std::size_t deallocations;
    std::size_t allocated;
    std::size_t unallocated;
    std::size_t nodes;

    friend memory_debugger;

    void coalesce()
    {

    }

  public:
    manager() : pool(nullptr), pool_size(0), fit(allocation_policy::none), allocations(0), deallocations(0), allocated(0), unallocated(0), nodes(0)
    {

    }

    ~manager()
    {

    }

    void init(std::size_t s, allocation_policy f)
    {
      pool = (std::byte*)malloc(s);
      pool_size = s;
      fit = f;
    }

    void shutdown()
    {
      // TODO: check for unreleased objects
      // TODO: take data on usage over time
      free(pool);
      pool_size = 0;
      fit = allocation_policy::none;
      allocations = 0;
      deallocations = 0;
      allocated = 0;
      unallocated = 0;
      nodes = 0;
    }

    void * allocate(std::size_t s)
    {
      ++allocated;
      ++allocations;
      return nullptr;
    }

    void deallocate(void * ptr)
    {
      ++deallocations;
      ++unallocated;
    }

    std::size_t size() const
    {
      return pool_size;
    }

    void clean()
    {
      memset(pool, 0, pool_size); // zero out all memory
      allocated = 0;
      unallocated = 0;
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
    manage = other.manager;
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

  void memory_debugger::dealloc(void * ptr) 
  {
#ifdef DEBUG
    manage->deallocate(ptr); 
#endif // DEBUG
  }

  std::byte * memory_debugger::get_pool() 
  { 
#ifdef DEBUG
    return manage->pool; 
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
    man.init(size, fit);
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

void operator delete(void * ptr)
{
}

void operator delete[](void* ptr)
{
}

#endif // WE_USE_STD_MEMORY

