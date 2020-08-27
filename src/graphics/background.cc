#include "background.hpp"
#include "space.hpp"
#include "sprite.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "transform.hpp"
#include "scenemanager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    background::background(std::string const& name, std::string const& sprite_name) : object_management::gameobject(name)
    {
      add_component_v<sprite>(sprite_name);
    }

    std::shared_ptr<object_management::gameobject> background::add_background(std::string const& obj_name, std::string const& sprite_name)
    {
      auto scn = scenes::current_scene();
      auto sp_manager = scn->get_manager();
      auto sp = sp_manager->get_space("Background Space");
      auto obj = sp->add_object(obj_name);
      
      auto object_transform = obj->add_component<graphics::transform>();
      object_transform->set_position_in_screen_coordinates(screen_point2d(0.0f, 0.0f));
      object_transform->set_width_ratio(1.0f);
      object_transform->set_height_ratio(1.0f);

      
      obj->add_component_v<sprite>(sprite_name);
      auto sprt = dynamic_cast<graphics::sprite *>(obj->get_component<graphics::sprite>().get());

      //sprt->scale({ 0.807f, 0.807f }); // TODO: this is just covering up a bug
      
      return obj;
    }
  }
}