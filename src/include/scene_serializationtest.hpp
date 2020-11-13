
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
        friend class waifuengine::core::debug::imgui_listener;


      public:
        SCENE_NAME(scene_serializationtest);

        scene_serializationtest();
        virtual ~scene_serializationtest();
      };
    }
  }
}


#endif