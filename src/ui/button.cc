#include "button.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "mouse_collider.hpp"
#include "window.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "debug_draw.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    button::button(std::string const& name, std::string const& sprite_name, std::string const& text) : object_management::gameobject(name)
    {
      auto spr = dynamic_cast<graphics::sprite *>(add_component_v<graphics::sprite>(sprite_name).get());
      auto col = dynamic_cast<physics::collider *>(add_component_v<physics::collider>().get());
      col->set_dimensions({0.25f, 0.25f});
      auto dd = add_component_v<graphics::debug_draw>();
    }

    button::~button()
    {

    }

    object_management::objectptr add_button(std::string const& name, std::string const& sprite_name, std::string const& text)
    {
       auto scn = scenes::current_scene();
      auto sp_manager = scn->get_manager();
      auto sp = sp_manager->get_space("UI Space");
      auto obj = sp->add_object_t<button>(name, sprite_name, text);
      return obj;

    }
  }
}