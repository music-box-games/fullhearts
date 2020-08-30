#include <sstream>

#include "button.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "mouse_collider.hpp"
#include "window.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "debug_draw.hpp"
#include "transform.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    button::button(std::string const& name, std::string const& sprite_name, std::string const& text, graphics::screen_point2d pos, glm::vec2 ratios) : object_management::gameobject(name)
    {
      {
        std::stringstream ss;
        ss << "Constructing button: {" << '\n' 
        << "name=" << name << ",\n"
        << "sprite_name=" << sprite_name << ",\n"
        << "text=" << text << ",\n"
        << "pos={" << pos.x << ',' << pos.y << "},\n"
        << "ratios={" << ratios.x << ',' << ratios.y << "}\n"
        << "}";
        log::LOGTRACE(ss.str());
      }
      auto obj_trans = add_component<graphics::transform>();
              obj_trans->set_position_in_screen_coordinates(pos);
        obj_trans->set_ratios(ratios);
      auto spr = add_component_v<graphics::sprite>(sprite_name);
      auto col = add_component_v<physics::collider>();
    }

    button::~button()
    {
      {
        std::stringstream ss;
        ss << "Destructing button: " << name();
        log::LOGTRACE(ss.str());
      }
    }

    object_management::objectptr add_button(std::string const& name, std::string const& sprite_name, std::string const& text, graphics::screen_point2d pos, glm::vec2 ratios)
    {
       auto scn = scenes::current_scene();
      auto sp_manager = scn->get_manager();
      auto sp = sp_manager->get_space("UI Space");
      auto obj = sp->add_object_t<button>(name, sprite_name, text, pos, ratios);
      return obj;

    }
  }
}