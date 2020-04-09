#ifndef _WE_THREAD_POOL_HPP_
#define _WE_THREAD_POOL_HPP_

#include <cstddef> // std::size_t

namespace waifuengine
{
  namespace core
  {
    namespace thread_pool
    {
      typedef void(*task)(void);

      void init();
      void update();
      void shutdown();

      std::size_t max_concurrent_tasks();

      void assign_task(task t);
    }
  }
}

#endif // !_WE_THREAD_POOL_HPP_