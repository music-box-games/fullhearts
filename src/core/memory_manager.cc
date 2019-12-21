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
    static constexpr std::size_t DEFAULT_SIZE = we::utils::hardware::GIGABYTE;
    char * pool; // memory pool
    bool initialized;
    std::size_t total_size;

  public:
    manager() : initialized(false), total_size(0)
    {

    }

    ~manager()
    {

    }

    void init(std::size_t size)
    {
      total_size = size;
      pool = (char*)malloc(size);
      initialized = true;
    }

    bool is_initialized() const
    {
      return initialized;
    }

    void release()
    {
      free(pool);
      total_size = 0;
      initialized = false;
    }

    void * allocate(std::size_t size)
    {
      return nullptr;
    }

    void free(void * ptr)
    {
      
    }

    std::size_t size() const 
    {
      return total_size;
    }
  };

  static manager man;

  void init(std::size_t size)
  {
    man.init(size);
  }

  void shutdown()
  {
    // TODO: check for unreleased memory
    // TODO: if debug gather stats about session
    man.release();
  }

  std::size_t size()
  {
    return man.size();
  }
}
} // namespace core
} // namespace waifuengine

#ifndef WE_USE_STD_MEMORY

void * operator new(std::size_t size)
{
  if(we::core::memory::man.is_initialized())
  {
    return we::core::memory::man.allocate(size);
  }
  else
  {
    return malloc(size);
  }
  
}

void operator delete(void * ptr)
{
  if(we::core::memory::man.is_initialized())
  {
    we::core::memory::man.free(ptr);
  }
  else
  {
    free(ptr);
  }
  
}

#endif // WE_USE_STD_MEMORY

