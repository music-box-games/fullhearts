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
    button::button(std::string const& name, std::string const& sprite_name, std::string const& text, glm::vec2 pos, glm::vec2 ratios) : object_management::gameobject(name)
    {
    }

    button::~button()
    {
    }

    
  }
}