#ifndef _WE_BUTTON_FACTORY_HPP_
#define _WE_BUTTON_FACTORY_HPP_

#include <gameobject.hpp>
#include <space.hpp>
#include <functional>

namespace waifuengine
{
  namespace factory
  {
    typedef waifuengine::object_management::gameobject button;

    class button_factory
    {
    public:
      static std::shared_ptr<button> build_textbutton(std::string name, std::string file, std::string text, std::function<void()> f = {},std::shared_ptr<waifuengine::object_management::space> space = {});
      static std::shared_ptr<button> build_imagebutton(std::string name, std::string file, std::function<void()> f = {}, std::shared_ptr<waifuengine::object_management::space> space = {});
    };
  }
}

#endif