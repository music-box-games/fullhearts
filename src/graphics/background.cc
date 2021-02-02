#include "background.hpp"
#include "sprite.hpp"

namespace waifuengine
{
  namespace graphics
  {
    background::background(std::string name, fs::path texture_file) : object_management::gameobject(name)
    {
      add_component_v<sprite>(texture_file);
    }
  }
}