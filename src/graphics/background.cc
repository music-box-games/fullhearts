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
            // add background's transform
      auto object_transform = add_component<graphics::transform>();
      // set transform to center of window
      object_transform->set_position_in_screen_coordinates(screen_point2d(0.0f, 0.0f));
      // set the width and height ratio to fill the window
      object_transform->set_ratios({1.f, 1.f});

            // add sprite to object
      auto spr = add_component_v<sprite>(sprite_name);
      // lock sprite to parent transform
      spr->lock_transform_to_parent_transform();
    }

    std::shared_ptr<object_management::gameobject> background::add_background(std::string const& obj_name, std::string const& sprite_name)
    {
      auto scn = scenes::current_scene();
      auto sp_manager = scn->get_manager();
      auto sp = sp_manager->get_space("Background Space");
      auto obj = sp->add_object_t<background>(obj_name, sprite_name);

      
      return obj;
    }
  }
}