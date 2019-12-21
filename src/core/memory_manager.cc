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
#include <vector>

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
  static constexpr std::size_t DEFAULT_NODE_ADD = 1000000;
  bool initialized;
  std::size_t total_size;

  struct memory_block
  {
    void *memory = nullptr;
    std::size_t size = 0;
    bool allocated = false;
  };

  struct node
  {
    node *prev;
    node *next;
    memory_block data;
  };

  node *head;
  node *tail;

  std::unordered_map<void *, node *> allocated_nodes;   // cache of allocated nodes to make freeing faster
  std::unordered_map<void *, node *> unallocated_nodes; // for making it easier to grab a free block
  std::vector<node *> fresh_nodes;                      // for making it easier to get a fresh node

  void add_fresh_nodes(std::size_t count)
  {
    for (int i = 0; i < count; ++i)
    {
      fresh_nodes.push_back(build_node());
    }
  }

  node *build_node()
  {
    node *n = (node *)malloc(sizeof(node));
    n->prev = nullptr;
    n->next = nullptr;
    return n;
  }

  void free_node(node *n)
  {
    free(n);
  }

  void push_front(node *n)
  {
    head->prev = n;
    n->next = head;
    head = n;
  }

  void push_back(node *n)
  {
    n->prev = tail;
    tail->next = n;
    tail = n;
  }

  void split_node(node *n, std::size_t nsize)
  {
    // TODO: double check this when it isn't 4:20am

    // get a fresh node
    node *nxt;
    if (fresh_nodes.empty())
      add_fresh_nodes(DEFAULT_NODE_ADD); // add more fresh nodes if there are none available
    nxt = fresh_nodes.back();
    fresh_nodes.pop_back(); // remove node from fresh list

    nxt->prev = n;
    nxt->next = n->next;
    nxt->data.allocated = false;
    nxt->data.memory = (char *)n->data.memory + nsize;
    nxt->data.size = n->data.size - nsize;

    n->next = nxt;
    n->data.size = nsize;

    // add the fresh node to the unallocated list
    unallocated_nodes[nxt->data.memory] = nxt;
  }

  node *get_unallocated_node(std::size_t min_size)
  {
    for (auto &n : unallocated_nodes)
    {
      if (n.second->data.size >= min_size) return n.second;
    }
    // TODO: handle case when there are no nodes that fit
    return nullptr;
  }

  void consolidate()
  {
  }

  node *find(void *address)
  {
#ifdef MEMMANAGE_CACHING
    if (allocated_nodes.count(address))
    {
      return allocated_nodes[address];
    }
    return nullptr;
#else
    node *temp = head;
    while (temp)
    {
      if (temp->data.memory == address)
        return temp;
    }
    return nullptr;
#endif // MEMMANAGE_CACHING
  }

public:
  manager() : initialized(false), total_size(0), head(nullptr), tail(nullptr)
  {
  }

  ~manager()
  {
  }

  void init(std::size_t size)
  {
    add_fresh_nodes(DEFAULT_NODE_ADD);
    total_size = size;
    // set first block
    node *n = build_node();
    head = n;
    tail = n;
    n->data.memory = malloc(size);
    n->data.size = size;
    n->data.allocated = false;
    unallocated_nodes[n->data.memory] = n;
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

  void *allocate(std::size_t size)
  {
    node *ret = get_unallocated_node(size);
    split_node(ret, size);
    ret->data.allocated = true;
    // remove node from list of unallocated
    unallocated_nodes.erase(ret->data.memory);
    // mark node in cache of allocated blocks
    allocated_nodes[ret->data.memory] = ret;
    return ret->data.memory;
  }

  void free(void *ptr)
  {
    node *n = find(ptr);
    if (n)
      n->data.allocated = false;
    // else do error handling
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
} // namespace memory
} // namespace core
} // namespace waifuengine

#ifndef WE_USE_STD_MEMORY

void *operator new(std::size_t size)
{
  if (we::core::memory::man.is_initialized())
  {
    return we::core::memory::man.allocate(size);
  }
  else
  {
    return malloc(size);
  }
}

void operator delete(void *ptr)
{
  if (we::core::memory::man.is_initialized())
  {
    we::core::memory::man.free(ptr);
  }
  else
  {
    free(ptr);
  }
}

#endif // WE_USE_STD_MEMORY
