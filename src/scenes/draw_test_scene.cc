/******************************************************************************/
/*!
\file   draw_test_scene.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Test scene for draw testing.

*/
/******************************************************************************/

#include <draw_test_scene.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <background.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    draw_test_scene::draw_test_scene() : scene(std::string(NAME))
    {
      std::shared_ptr<::waifuengine::object_management::space> sp = manager.add_space("Background Space");
      we::graphics::background_factory::build_background("test background", "./bin/assets/images/test/wallpaper.bmp", sp);
    }

    draw_test_scene::~draw_test_scene()
    {
      manager.remove_object("test object");
    }
  }
}
