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

#include <frozen/set.h>

#include <benchmark.hpp>

namespace waifuengine
{
  namespace benchmarks
  {
    void memory_allocation_test()
    {

    }

    static constexpr frozen::set<std::function<void()>> tests = 
    {
      memory_allocation_test,
    };

    void run()
    {
      
    }
  }
}