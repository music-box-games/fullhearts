#ifndef _WE_SCENE_SANDBOX_HPP_
#define _WE_SCENE_SANDBOX_HPP_

#include "scenes.hpp"
#include "events.hpp"

namespace waifuengine
{
  namespace scenes
  {
    // class scene_sandbox : public scene
    // {
    // public:
    //   SCENE_NAME(scene_sandbox);
    //   scene_sandbox();
    //   virtual ~scene_sandbox();

    // private:
    //   friend class imgui_listener;
    //   friend class boost::serialization::access;
    //   template<class Archive>
    //   void serialize(Archive& ar, unsigned int const v)
    //   {
    //     ar & boost::serialization::base_object<scene>(*this);
    //   }
    // };

    std::shared_ptr<scene> build_sandbox_scene();
  }
}


#endif