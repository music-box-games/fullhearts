#include <sstream>

#include "button.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "window.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "transform.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    button::button(std::string const& name, fs::path texture_file, std::string const& text) : object_management::gameobject(name)
    {
      add_component_v<graphics::sprite>(texture_file);
    }

    button::~button()
    {
    }

    
  }
}