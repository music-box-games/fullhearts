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
    class serializable_dummy; // forward ref  
    class dummy : public component<dummy>
    {
    private:
      int dumb;

    public:
      COMPONENT_NAME(dummy);
      COMPONENT_TYPE(dummy);

      dummy();
      dummy(dummy const& other);
      dummy(serializable_dummy const& other);
      virtual ~dummy();

      virtual void update(float dt);
      virtual void draw() const;

      void set_data(int d);
      int get_data() const;

      void operator=(dummy const& rhs);
      bool operator==(dummy const& rhs);

    private:
      friend class serializable_dummy;
    };

    class serializable_dummy : public serializable_component
    {
    private:
      int dumb;

      friend class dummy;
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive const& ar, unsigned int const version)
      {
        ar & dumb;
      }
    public:
      serializable_dummy();
      serializable_dummy(waifuengine::components::dummy const& rhs);
      virtual ~serializable_dummy();
    };
  }
}

#endif // !_WE_DUMMY_HPP_
