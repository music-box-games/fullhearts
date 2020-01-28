#ifndef _WE_SCENE_MM_HPP_
#define _WE_SCENE_MM_HPP_

#include <scenes.hpp>

namespace waifuengine
{
  namespace scenes
  {
    class scene_mainmenu : public scene
    {
    public:
      SCENE_NAME(scene_mainmenu);
      scene_mainmenu();
      virtual ~scene_mainmenu();

    };
  }
}

#endif