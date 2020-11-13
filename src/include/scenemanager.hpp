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
#include <scenes.hpp>
#include <log.hpp>
#include <debug.hpp>
#include <utils.hpp>

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
        std::function<void()> scene_loader;

        friend class waifuengine::core::debug::imgui_listener;

        void unload_scene();
        void load_scene();
        void update_scene_saves();

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

        bool operator==(scene_manager const &rhs) const;

        void queue_scene(std::function<void()> sl);

        static std::unordered_map<std::string, fs::path> &get_scene_list();
      };

      extern scene_manager *smanager;
    } // namespace impl

    void load(std::string name);
    void unload();
    void save();
    using scene_loader = std::function<void()>;
    void queue_scene(scene_loader sl);

    void init();
    void shutdown();
    void update(float dt);
    void draw();

    std::shared_ptr<scene> blank_scene(std::string name);
    std::shared_ptr<scene> current_scene();
  } // namespace scenes
} // namespace waifuengine


#endif // !_WE_SCENE_MANAGER_HPP_
