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
    dummy::dummy(dummy const& other) : component<dummy>(), dumb(other.dumb) {}
    dummy::dummy(serializable_dummy const& other) : component<dummy>(), dumb(other.dumb) {}

    dummy::~dummy() {}

    void dummy::set_data(int d)
    {
      dumb = d;
    }

    int dummy::get_data() const
    {
      return dumb;
    }

    void dummy::update(float) {}
    void dummy::draw() const {}

    void dummy::operator=(dummy const& rhs)
    {
      dumb = rhs.dumb;
    }

    bool dummy::operator==(dummy const& rhs)
    {
      return dumb == rhs.dumb;
    }

    serializable_dummy::serializable_dummy() : serializable_component(dummy::NAME, dummy::TYPE) {}
    serializable_dummy::serializable_dummy(dummy const& other) : serializable_component(dummy::NAME, dummy::TYPE), dumb(other.dumb) {}
    serializable_dummy::~serializable_dummy() {}
  }
}
