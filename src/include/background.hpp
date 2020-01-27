#ifndef _WE_BACKGROUND_HPP_
#define _WE_BACKGROUND_HPP_

#include <gameobject.hpp>
#include <sprite.hpp>
#include <spacemanager.hpp>

namespace waifuengine
{
  namespace graphics
  {
    typedef we::object_management::gameobject background;

    class background_factory
    {
    public:
      static std::shared_ptr<background> build_background(std::string name, std::string file, std::shared_ptr<we::object_management::space> space = {});
    };
  }
}

#endif // !_WE_BACKGROUND_HPP_