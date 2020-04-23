#ifndef _WE_SERIALIZATION_HPP_
#define _WE_SERIALIZATION_HPP_

#include <string>

#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace serialization
    {
      
      namespace test
      {
        class test_serialize_object
        {
        public:
          test_serialize_object(int a, int b, int c, std::string text);

          bool operator==(test_serialize_object const& rhs);

          int a, b, c;
          std::string text;

        protected:
          friend class boost::serialization::access;
          template<typename Archive>
          void serialize(Archive& ar, unsigned int const v)
          {
            ar & a;
            ar & b;
            ar & c;
            ar & text;
          }
        };

        class derived_test_serialize_object : public test_serialize_object
        {
        public:
          derived_test_serialize_object(int a, int b, int c, std::string text, int d);
          bool operator==(derived_test_serialize_object const& rhs);

        protected:
          friend class boost::serialization::access;
          int d;

          template<class Archive>
          void serialize(Archive& ar, unsigned int const v)
          {
            ar & boost::serialization::base_object<test_serialize_object>(*this);
            ar & d;
          }
        };
      }
    }
  }
}

#endif
