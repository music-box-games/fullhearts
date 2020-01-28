/******************************************************************************/
/*!
\file   scenes.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Scene class, responible for managing it's own space manager

*/
/******************************************************************************/

#include <scenes.hpp>

#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    scene::scene(std::string n) : name(n)
    {
      std::stringstream ss;
      ss << "scene \"" << name << "\" constructing";
      we::log::trace(ss.str());
    }

    scene::~scene()
    {
      std::stringstream ss;
      ss << "scene \"" << name << "\" destructing";
      we::log::trace(ss.str());
    }

    void scene::update(float dt)
    {
      manager.update(dt);
    }

    void scene::draw() const
    {
      manager.draw();
    }

    we::object_management::space_manager * scene::get_manager()
    {
      return &manager;
    }
  }
}
