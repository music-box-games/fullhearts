#include <scene_mm.hpp>

namespace waifuengine
{
namespace scenes
{
  scene_mainmenu::scene_mainmenu() : scene(std::string(NAME))
  {
    auto sps = manager.build_default_spaces();
  }

  scene_mainmenu::~scene_mainmenu()
  {

  }
}
} // namespace waifuengine