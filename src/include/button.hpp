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
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, unsigned int const v)
      {
        ar & boost::serialization::base_object<waifuengine::object_management::gameobject>(*this);
      }

    public:
      button(std::string const& name, std::string const& sprite_name, std::string const& text = "");
      virtual ~button();
    };

    object_management::objectptr add_button(std::string const& name, std::string const& sprite_name, std::string const& text = "");
  }
}

#endif