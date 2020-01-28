#ifndef _WE_SCENE_SPLASHSCREEN_HPP_
#define _WE_SCENE_SPLASHSCREEN_HPP_

#include <scenes.hpp>

namespace waifuengine
{
  namespace scenes
  {
    class scene_splashscreen : public scene 
    {
    public:
      SCENE_NAME(scene_splashscreen);
      scene_splashscreen();
      virtual ~scene_splashscreen();
    };
  }
}

#endif // !_WE_SCENE_SPLASHSCREEN_HPP_