/******************************************************************************/
/*!
\file   allocator.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Custom allocator class for memory management

*/
/******************************************************************************/

#include <allocator.hpp>

namespace waifuengine
{
namespace core
{
namespace memory
{
  allocator::block::block(std::size_t sz) : head({head.allocated = false, head.size = sz}), next(nullptr), data(nullptr) {}

  allocator::block::~block() {}

  allocator::page::page(std::size_t psize, std::size_t dsize) : head({head.size = psize, head.max_objects = 0, head.object_size = dsize, head.object_count = 0}),
  next(nullptr), pool(nullptr), blocklist(nullptr)
  {
    // TODO: write debug patterns if debug build
  }

  allocator::page::~page() {}

  allocator::page_list::page_list(std::size_t psize, std::size_t dsize) : head({head.page_count = 0, head.page_size = psize, head.object_count = 0, head.object_size = dsize}),
  pg(nullptr)
  {
    
  }

  allocator::page * allocator::page_list::add_front()
  {
    // TODO: allocate new page and insert it at front of list
    return nullptr;
  }

  allocator::page * allocator::page_list::add_back()
  {
    // TODO: allocate new page and insert it at end of list
    return nullptr;
  }

  std::size_t allocator::page_list::padding() const
  {
    // TODO: calculate padding between each object in a page
    return 0;
  }

  allocator::allocator(std::size_t psize, std::size_t dsize) : header(nullptr), datasize(dsize), pagesize(psize), pool(nullptr)
  {
    // TODO: allocate pool and add first page
  }

  allocator::~allocator()
  {
    // TODO: free pool and page list
  }

  void allocator::reset(std::size_t psize, std::size_t dsize)
  {
    // TODO: free pages and add accomodate for new sizes
  }
}
}
}
