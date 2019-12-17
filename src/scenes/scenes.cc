
#include <scenes.hpp>

#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    scene::scene(std::string n) : NAME(n)
    {
      std::stringstream ss;
      ss << "scene \"" << NAME << "\" constructing";
      we::log::trace(ss.str());
    }

    scene::~scene()
    {
      std::stringstream ss;
      ss << "scene \"" << NAME << "\" destructing";
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
  }
}
