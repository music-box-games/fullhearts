/******************************************************************************/
/*!
\file   memory_manager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Custom memory management.

*/
/******************************************************************************/

#ifndef _WE_MEMORY_MANAGER_HPP_
#define _WE_MEMORY_MANAGER_HPP_

#define WE_USE_STD_MEMORY
#define MEMMANAGE_CACHING


namespace waifuengine
{
namespace core
{
namespace memory
{
  namespace allocation_policies
  {
    enum class sequential
    {
      first_fit,
      best_fit,
      next_fit,
    };
  }
  enum class allocation_policy
  {
    first_fit,
    best_fit,

    // special
    none,
  };
  class manager;

  class memory_debugger
  {
  private:
    manager* manage;

  public:
    memory_debugger(void* m);
    memory_debugger(memory_debugger& other);
    ~memory_debugger();

    void * alloc(std::size_t s);
    void dealloc(void * p, std::size_t s);

    std::byte * get_pool();
  };

  void init(std::size_t size, allocation_policy fit);
  void shutdown();
  memory_debugger attach_debugger();
} // namespace memory
} // namespace core
} // namespace waifuengine

#endif // !_WE_MEMORY_MANAGER_HPP_