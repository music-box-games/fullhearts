/******************************************************************************/
/*!
\file   collider.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Collider component

*/
/******************************************************************************/

#include <collider.hpp>
#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace physics
{
  collider::collider() : we::components::component<collider>()
  {

  }

  collider::~collider() {}
}
} // namespace waifuengine

BOOST_CLASS_EXPORT_IMPLEMENT(waifuengine::physics::collider);