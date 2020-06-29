#ifndef _WE_SCENE_SPLASHSCREEN_HPP_
#define _WE_SCENE_SPLASHSCREEN_HPP_

#include <memory>
#include "scenes.hpp"

namespace waifuengine
{
  namespace scenes
  {
    std::shared_ptr<scene> build_splashscreen_scene();
  }
}

#endif