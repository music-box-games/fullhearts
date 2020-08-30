#ifndef _WE_BUTTON_HPP_
#define _WE_BUTTON_HPP_

#include "gameobject.hpp"
#include "point2d.hpp"

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
      button(std::string const& name, std::string const& sprite_name, std::string const& text = "", graphics::screen_point2d pos = {0.f,0.f}, glm::vec2 ratios = {1.f,1.f});
      virtual ~button();
    };

    object_management::objectptr add_button(
      std::string const& name, 
      std::string const& sprite_name, 
      std::string const& text = "", 
      graphics::screen_point2d pos = graphics::screen_point2d(),
      glm::vec2 screen_ratios = glm::vec2(1.f, 1.f)
      );
  }
}

#endif