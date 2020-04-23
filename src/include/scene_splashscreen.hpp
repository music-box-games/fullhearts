#ifndef _WE_SCENE_SPLASHSCREEN_HPP_
#define _WE_SCENE_SPLASHSCREEN_HPP_

#include <scenes.hpp>
#include <events.hpp>

namespace waifuengine
{
  namespace scenes
  {
    class scene_splashscreen : public scene 
    {
    public:
      SCENE_NAME(scene_splashscreen);
      scene_splashscreen();
      virtual ~scene_splashscreen();
    private:
      void input_handler(waifuengine::events::event * ievent);
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const version)
      {
        ar & boost::serialization::base_object<scene>(*this);
      }
    };
  }
}

BOOST_CLASS_EXPORT_KEY(we::scenes::scene_splashscreen);

#endif // !_WE_SCENE_SPLASHSCREEN_HPP_