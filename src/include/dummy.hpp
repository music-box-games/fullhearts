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
#include <serialization.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace components
  {
    class dummy : public component<dummy>
    {
    private:
      friend class boost::serialization::access;
      int dumb;

      template<class Archive>
      void serialize(Archive& ar, unsigned int const)
      {
        ar & boost::serialization::base_object<component<dummy>>(*this);
        ar & dumb;
      }

    public:
      COMPONENT_NAME(dummy);
      COMPONENT_TYPE(dummy);

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
BOOST_CLASS_EXPORT_KEY(we::components::dummy);

#endif // !_WE_DUMMY_HPP_
