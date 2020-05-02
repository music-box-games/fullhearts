/******************************************************************************/
/*!
\file   scenemanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Manages scenes. Scenes contain a space manager, which contains spaces, which 
  contain objects, which contain components. The Scene manager is the top dog for
  controlling stuff.

*/
/******************************************************************************/

#ifndef _WE_SCENE_MANAGER_HPP_
#define _WE_SCENE_MANAGER_HPP_

#include <string>
#include <utility>
#include <memory>
#include <sstream>
#include <functional>

#include <component.hpp>
#include <serialization.hpp>
#include <scenes.hpp>
#include <log.hpp>
#include <debug.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    namespace impl
    {
      // manages scenes, can only handle one of each scene currently
      class scene_manager
      {
      private:
        using scene_container = std::pair<std::string, std::shared_ptr<::waifuengine::scenes::scene>>;
        scene_container smap;

        bool queued_for_load = false;
        bool queued_for_unload = false;
        std::string queued_scene = "";

        friend class waifuengine::core::debug::imgui_listener;  
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const version)
        {
          ar & smap;
        }

        void unload_scene();
        void load_scene();

      public:
        scene_manager();
        ~scene_manager();

        void update(float dt);

        void draw() const;

        void load(std::string name);
        void unload();
        void save();

        std::shared_ptr<scene> blank_scene(std::string name);
        std::shared_ptr<scene> current_scene();

        bool operator==(scene_manager const& rhs) const;
      };

      extern scene_manager * smanager;
    }

    void load(std::string name);
    void unload();
    void save();

    void init();
    void shutdown();
    void update(float dt);
    void draw();


    std::shared_ptr<scene> blank_scene(std::string name);
    std::shared_ptr<scene> current_scene();
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::scenes::impl::scene_manager);

#endif // !_WE_SCENE_MANAGER_HPP_
