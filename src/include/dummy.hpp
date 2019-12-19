/******************************************************************************/
/*!
\file   dummy.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  dummy component for testing.

*/
/******************************************************************************/

#ifndef _WE_DUMMY_HPP_
#define _WE_DUMMY_HPP_

#include <component.hpp>

namespace waifuengine
{
  namespace components
  {
    class dummy : public component<dummy>
    {
    public:
      COMPONENT_NAME(dummy);
      COMPONENT_TYPE(dummy);

      dummy();
      virtual ~dummy();

      virtual void update(float dt);
      virtual void draw() const;
    };
  }
}

#endif // !_WE_DUMMY_HPP_
