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

        bool queued = false;
        std::function<void()> qf;

        friend class waifuengine::core::debug::imgui_listener;  
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, unsigned int const version)
        {
          ar & smap;
        }

      public:
        scene_manager();
        ~scene_manager();

        void update(float dt);
        void draw() const;

        template<typename Scene>
        void load()
        {
          std::string sname(Scene::NAME);
          smap.first = sname;
          smap.second = std::shared_ptr<::waifuengine::scenes::scene>(new Scene());
        }

        template<typename Scene>
        void queue_load()
        {
          qf = std::bind(&scene_manager::load<Scene>, this);
          queued = true;
        }

        template<typename Scene>
        void unload()
        {
          smap.first = "";
          smap.second.reset();
        }

        std::shared_ptr<scene> current_scene();

        bool operator==(scene_manager const& rhs) const;
      };

      extern scene_manager * smanager;
    }

    template<typename Scene>
    void load()
    {
      std::stringstream ss;
      ss << "loading scene: " << Scene::NAME;
      we::log::trace(ss.str());
      
      impl::smanager->load<Scene>();
    }

    template<typename Scene>
    void queue_load()
    {
      std::stringstream ss;
      ss << "Queueing scene " << Scene::NAME;
      we::log::trace(ss.str());
      impl::smanager->queue_load<Scene>();
    }

    template<typename Scene>
    void unload()
    {
      impl::smanager->unload<Scene>();
    }

    void init();
    void shutdown();
    void update(float dt);
    void draw();

    std::shared_ptr<scene> current_scene();
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::scenes::impl::scene_manager);

#endif // !_WE_SCENE_MANAGER_HPP_
