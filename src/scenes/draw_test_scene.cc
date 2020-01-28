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

namespace we = ::waifuengine;

namespace waifuengine
{
namespace scenes
{
draw_test_scene::draw_test_scene() : scene(std::string(NAME))
{
}

draw_test_scene::~draw_test_scene()
{
}
} // namespace scenes
} // namespace waifuengine
