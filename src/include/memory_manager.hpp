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

//#define WE_USE_STD_MEMORY
#define MEMMANAGE_CACHING


namespace waifuengine
{
namespace core
{
namespace memory
{
  void init(std::size_t size);
  void shutdown();
  std::size_t size();
} // namespace memory
} // namespace core
} // namespace waifuengine

#endif // !_WE_MEMORY_MANAGER_HPP_