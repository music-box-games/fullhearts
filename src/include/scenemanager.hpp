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
#include <unordered_map>
#include <memory>
#include <sstream>

#include <scenes.hpp>
#include <log.hpp>

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
        using scene_container = std::unordered_map<std::string, std::shared_ptr<::waifuengine::scenes::scene>>;
        scene_container smap;

      public:
        scene_manager();
        ~scene_manager();

        void update(float dt);
        void draw() const;

        template<typename Scene>
        void load()
        {
          std::string sname(Scene::NAME);
          if(smap.count(sname))
          {
            smap.erase(sname);
          }
          smap[sname] = std::shared_ptr<::waifuengine::scenes::scene>(new Scene());
        }

        template<typename Scene>
        void unload()
        {
          std::string sname(Scene::NAME);
          if(smap.count(sname))
          {
            smap.erase(sname);
          }
        }
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
    void unload()
    {
      impl::smanager->unload<Scene>();
    }

    void init();
    void shutdown();
    void update(float dt);
    void draw();
  }
}

#endif // !_WE_SCENE_MANAGER_HPP_
