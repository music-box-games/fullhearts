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
#include <basic_shape.hpp>

namespace waifuengine
{
  namespace scenes
  {
    draw_test_scene::draw_test_scene() : scene(std::string(NAME))
    {
      std::shared_ptr<::waifuengine::object_management::space> sp = manager.add_space("test space");
      std::shared_ptr<::waifuengine::object_management::gameobject> o = sp->add_object("test object");
      std::shared_ptr<::waifuengine::components::basic_triangle> tr = o->add_component<::waifuengine::components::basic_triangle>();
    }

    draw_test_scene::~draw_test_scene()
    {
      manager.remove_object("test object");
    }
  }
}
