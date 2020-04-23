
#ifndef _WE_SCENE_SERIALIZATIONTEST_HPP_
#define _WE_SCENE_SERIALIZATIONTEST_HPP_

#include <scenes.hpp>

namespace waifuengine
{
  namespace scenes
  {
    namespace test
    {
      class scene_serializationtest : public ::waifuengine::scenes::scene
      {
      private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const version)
        {
          ar & boost::serialization::base_object<::waifuengine::scenes::scene>(*this);
        }

      public:
        SCENE_NAME(scene_serializationtest);

        scene_serializationtest();
        virtual ~scene_serializationtest();
      };
    }
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::scenes::test::scene_serializationtest);

#endif