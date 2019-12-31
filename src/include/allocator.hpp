/******************************************************************************/
/*!
\file   allocator.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Custom allocator class for memory management

*/
/******************************************************************************/

#ifndef _WE_ALLOCATOR_HPP_
#define _WE_ALLOCATOR_HPP_

#include <cstddef> // std::byte, std::size_t
#include <cstdlib> // std::malloc
#include <unordered_map>

#include <hardware.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace memory
    {
      class allocator
      {
      private:
        static constexpr unsigned char PATTERN_PADDING_GUARD = 0xFB;
        static constexpr unsigned char PATTERN_PADDING_ALIGN = 0xFC;
        static constexpr unsigned char PATTERN_ALLOCATED = 0xFD;
        static constexpr unsigned char PATTERN_UNALLOCATED = 0xFE;
        static constexpr unsigned char PATTERN_FREED = 0xFF;

        static constexpr std::size_t DEFAULT_PAGE_SIZE_B = waifuengine::utils::hardware::MEGABYTE;

        class block
        {
        public:
          struct header
          {
            bool allocated; // if the block is currently allocated
            std::size_t size; // usuable size of object
          };

          header head; // block header info
          block * next; // next block
          std::byte * data; // block data

          // Constructor
          // inputs:
          //  s - usuable size of object
          block(std::size_t s);
          // Destructor
          ~block();
        };

        class page
        {
        public:
          struct header
          {
            std::size_t size; // size of usuable data in page
            std::size_t max_objects; // max possible objects that can be stored in page
            std::size_t object_size; // usuable size of objects
            std::size_t object_count; // current number of objects
          };

          header head; // header info
          page * next; // next page
          std::byte * pool; // data reserved for this pool
          block * blocklist; // list of blocks

          // Constructor
          // input:
          //  psize - Usable size of each page
          //  dsize - Usable size of each object
          page(std::size_t psize, std::size_t dsize);
          // Destructor
          ~page();
        };

        class page_list
        {
        private:
          page * build_page();
        public:
          struct header
          {
            std::size_t page_count; // number of pages
            std::size_t page_size; // size of usuable data in each page
            std::size_t object_count; // number of objects
            std::size_t object_size; // usuable size of objects
          };

          header head; // header info
          page * pg; // pointer for front page

          // Constructor
          // inputs:
          //  psize - Usable size of page data
          //  dsize - Usuable size of each object
          page_list(std::size_t psize, std::size_t dsize);
          // Destructor
          ~page_list();
          // Adds a new page to front of list
          page * add_front();
          // Adds a new page to end of list
          page * add_back();
          // Calculates total padding between objects
          std::size_t padding() const;
          
        };

        page_list * header; // list of pages
        std::size_t datasize; // usable size of each object
        std::size_t pagesize; // usable size of each page
        std::byte * pool; // pool of memory

#ifdef DEBUG
        friend class memory_debugger;
#endif // DEBUG

      public:
        // Constructor
        // input:
        //  psize - Usuable data size for each page
        //  dsize - Usable data size for each object
        allocator(std::size_t psize, std::size_t dsize);
        // Destructor
        ~allocator();
        // Resets the allocator for a different data or page size
        void reset(std::size_t psize, std::size_t dsize);

        void * allocate(std::size_t s);
        void deallocate(void * ptr);
      };

      // TODO: wrap this in ifdef debug
      class allocator_debugger
      {
      public:
        allocator * alloc;
        allocator_debugger(allocator * a);
        ~allocator_debugger();
      };
    }
  }
}

#endif // !_WE_ALLOCATOR_HPP_