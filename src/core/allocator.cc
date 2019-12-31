/******************************************************************************/
/*!
\file   allocator.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Custom allocator class for memory management

*/
/******************************************************************************/

#include <new>
#include <cstring>

#include <allocator.hpp>
#include <hardware.hpp>
#include <exceptions.hpp>

namespace we = ::waifuengine;

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

  allocator::page::~page() 
  {
    // walk through block list and call destructor on each
    auto * list = blocklist;
    while(list)
    {
      auto * temp = list;
      list = list->next;
      temp->~block(); // destruct
      free(temp); // free
    }
  }

  allocator::page_list::page_list(std::size_t psize, std::size_t dsize) : head({head.page_count = 0, head.page_size = psize, head.object_count = 0, head.object_size = dsize}),
  pg(nullptr)
  {
    // Allocate first page
    add_front();
  }

  allocator::page_list::~page_list()
  {
    auto * temp = pg; // get head of list
    // free each page
    while(temp)
    {
      auto * n = temp->next;
      temp->~page();
      free(temp);
      temp = n;
    }
  }

  allocator::page * allocator::page_list::build_page()
  {
    page * p = static_cast<page*>(malloc(sizeof(page)));
    if(p == nullptr)
    {
      throw std::bad_alloc();
    }
    p = new(p)page(head.page_size, head.object_size);
    return p;
  }

  allocator::page * allocator::page_list::add_front()
  {
    // allocate new page and insert it at front of list
    auto * p = build_page();
    p->next = pg;
    pg = p;
    ++head.page_count;
    return p;
  }

  allocator::page * allocator::page_list::add_back()
  {
    // allocate new page and insert it at end of list
    if(head.page_count == 0)
    {
      return add_front();
    }
    auto * p = build_page();
    auto * walk = pg, * prev = pg;
    while(walk)
    {
      prev = walk;
      walk = walk->next;
    }
    prev->next = p;
    ++head.page_count;
    return p;
  }

  std::size_t allocator::page_list::padding() const
  {
    // TODO: calculate padding between each object in a page
    throw we::core::exceptions::unimplemented();
    return 0;
  }

  allocator::allocator(std::size_t psize, std::size_t dsize) : header(nullptr), datasize(dsize), pagesize(psize), pool(nullptr)
  {
    // allocate pool
    pool = static_cast<std::byte*>(malloc(10 * we::utils::hardware::MEGABYTE));
    if(pool == nullptr)
    {
      // throw 
      throw std::bad_alloc();
    }
    // write unallocated pattern
    std::memset(pool, PATTERN_UNALLOCATED, 10 * we::utils::hardware::MEGABYTE);
    // allocate page list
    header = static_cast<page_list*>(malloc(sizeof(page_list)));
    if(header == nullptr)
    {
      throw std::bad_alloc();
    }
    header = new(header)page_list(psize, dsize);
  }

  allocator::~allocator()
  {
    // free pool and page list
    header->~page_list();
    free(header);
    free(pool);
  }

  void allocator::reset(std::size_t psize, std::size_t dsize)
  {
    // free pages and accomodate for new sizes
    header->~page_list();
    header = new(header)page_list(psize, dsize);
  }

  allocator_debugger::allocator_debugger(allocator * a) : alloc(a) {}
}
}
}
