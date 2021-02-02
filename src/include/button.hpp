#ifndef _WE_BUTTON_HPP_
#define _WE_BUTTON_HPP_

#include "gameobject.hpp"

namespace waifuengine
{
  namespace ui
  {
    class button : public object_management::gameobject
    {
    private:
 

    public:
      button(std::string const& name, std::string const& sprite_name, std::string const& text = "", glm::vec2 pos = {0.f,0.f}, glm::vec2 ratios = {1.f,1.f});
      virtual ~button();
    };

  }
}

#endif