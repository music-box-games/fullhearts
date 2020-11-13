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

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace components
  {
    class dummy : public component<dummy>
    {
    private:
      int dumb;

    public:
      COMPONENT_REGISTER(dummy);

      dummy();
      dummy(dummy const& other);

      virtual ~dummy();

      virtual void update(float dt);
      virtual void draw() const;

      void set_data(int d);
      int get_data() const;

      virtual void operator=(dummy const& rhs);
      virtual bool operator==(dummy const& rhs);
    };

  }
}

#endif // !_WE_DUMMY_HPP_
