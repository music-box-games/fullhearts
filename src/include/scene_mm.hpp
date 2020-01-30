#ifndef _WE_SCENE_MM_HPP_
#define _WE_SCENE_MM_HPP_

#include <scenes.hpp>
#include <events.hpp>

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
    private:
      void input_handler(waifuengine::events::event * e);
    };
  }
}

#endif