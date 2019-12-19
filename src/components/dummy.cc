/******************************************************************************/
/*!
\file   dummy.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Dummy component used for testing.

*/
/******************************************************************************/

#include <dummy.hpp>

namespace waifuengine
{
  namespace components
  {
    dummy::dummy() : component<dummy>() {}
    dummy::~dummy() {}

    void dummy::update(float) {}
    void dummy::draw() const {}
  }
}
