#ifndef _WE_SCENE_MM_HPP_
#define _WE_SCENE_MM_HPP_

#include <scenes.hpp>
#include <events.hpp>
#include <serialization.hpp>

namespace waifuengine
{
  namespace scenes
  {
    class scene_mainmenu : public scene
    {
    public:
      SCENE_NAME(scene_mainmenu);
      scene_mainmenu();
      virtual ~scene_mainmenu();
    private:
      void input_handler(waifuengine::events::event * e);
      void on_quit_click();
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const version)
      {
        ar & boost::serialization::base_object<scene>(*this);
      }
    };
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::scenes::scene_mainmenu);

#endif