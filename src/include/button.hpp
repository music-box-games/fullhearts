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
      button(std::string const& name, fs::path texture_file, std::string const& text = "");
      virtual ~button();
    };

  }
}

#endif