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
    bool initialized;
    std::size_t total_size;

    struct memory_block
    {
      void * memory = nullptr;
      std::size_t size = 0;
      bool allocated = false;
    };

    struct node
    {
      node * prev;
      node * next;
      memory_block data;
    };

    node * head;
    node * tail;

    std::unordered_map<void *, node *> allocated_blocks;

    node * build_node()
    {
      node * n = (node*)malloc(sizeof(node));
      n->prev = nullptr;
      n->next = nullptr;
      return n;
    }

    void free_node(node * n)
    {
      free(n);
    }

    void push_front(node * n)
    {
      head->prev = n;
      n->next = head;
      head = n;
    }

    void push_back(node * n)
    {
      n->prev = tail;
      tail->next = n;
      tail = n;
    }

    void split_node(node * n, std::size_t nsize)
    {
      // TODO: double check this when it isn't 4:20am
      // create new node to stick after the node being split
      node * nxt = build_node();
      nxt->prev = n;
      nxt->next = n->next;
      nxt->data.allocated = false;
      nxt->data.memory = (char*)n->data.memory + nsize;
      nxt->data.size = n->data.size - nsize;

      n->next = nxt;
      n->data.size = nsize;
    }

    void consolidate()
    {

    }

    node * find(void * address)
    {
      node * temp = head;
      while(temp)
      {
        if(temp->data.memory == address) return temp;
      }
      return nullptr;
    }

  public:
    manager() : initialized(false), total_size(0), head(nullptr), tail(nullptr), allocated_blocks({})
    {

    }

    ~manager()
    {

    }

    void init(std::size_t size)
    {
      total_size = size;
      // set first block
      node * n = build_node();
      head = n;
      tail = n;
      n->data.memory = malloc(size);
      n->data.size = size;
      n->data.allocated = false;
    }

    bool is_initialized() const
    {
      return initialized;
    }

    void release()
    {
      // TODO: release memory too
      total_size = 0;
      initialized = false;
    }

    void * allocate(std::size_t size)
    {
      node * ret = tail;
      split_node(ret, size);
      ret->data.allocated = true;
      // mark node in cache of allocated blocks
      return ret->data.memory;
    }

    void free(void * ptr)
    {
      // TODO: improve this by adding cache
      node * n = find(ptr);
      if(n) n->data.allocated = false;
      // else do error handling 
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
}
} // namespace core
} // namespace waifuengine

//#define WE_USE_STD_MEMORY
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

#endif // _WE_USE_STD_MEMORY

