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

namespace waifuengine
{
  namespace core
  {
    namespace memory
    {
      class allocator
      {
      private:
        static constexpr unsigned char PATTERN_ALIGN = 0xFC;
        static constexpr unsigned char PATTERN_ALLOC = 0xFD;
        static constexpr unsigned char PATTERN_FREE = 0xFE;

        class block
        {
        public:
          block * next;
          std::byte * data;

          block()
          {

          }
        };

        class page
        {
        public:
          page * next;
          std::byte * pool;
          block * blocklist;
        };

        page * pagelist;

        std::size_t datasize;
        std::size_t pagesize;

      public:
        allocator(std::size_t dsize, std::size_t psize) : pagelist(nullptr), datasize(dsize), pagesize(psize)
        {

        }
      };
    }
  }
}

#endif // !_WE_ALLOCATOR_HPP_