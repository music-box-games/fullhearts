#include <atomic>
#include <vector>

#include <boost/thread.hpp>
#include <thread_pool.hpp>
#include <hardware.hpp>

namespace waifuengine
{
namespace core
{
namespace thread_pool
{
  std::vector<boost::thread> threads;
  std::vector<task> queue;
  std::atomic_bool threads_should_exit = false;

  void init()
  {
    threads.reserve(utils::hardware::get_cpu_core_count());
  }

  void update()
  {
    
  }

  void shutdown()
  {
    // kill threads
    for(auto& t : threads)
    {
      t.interrupt();
    }
  }

  std::size_t max_concurrent_tasks()
  {
    return static_cast<std::size_t>(utils::hardware::get_cpu_core_count());
  }

  void assign_task(task t)
  {
    // add task to queue if already at mask tasks
    if(threads.size() == utils::hardware::get_cpu_core_count())
    {
      queue.push_back(t);
    }
    else
    {
      threads.push_back(boost::thread(t)); 
    }
  }
}
} // namespace core
} // namespace waifuengine
