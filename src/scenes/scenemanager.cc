/******************************************************************************/
/*!
\file   scenemanager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  The scene manager manages all existing scenes.

*/
/******************************************************************************/

#include <unordered_map>

#include <scenemanager.hpp>
#include <log.hpp>
#include <fs_util.hpp>
#include <serialization.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    namespace impl
    {
      static std::unordered_map<std::string, fs::path> scene_data;

      scene_manager * smanager = nullptr;

      scene_manager::scene_manager() : smap({})
      {
        we::log::trace("scene manager construction");
      }

      scene_manager::~scene_manager()
      {
        we::log::trace("scene manager destruction");
      }

      void scene_manager::update(float dt)
      {
        if(queued_for_load)
        {
          unload_scene();
          load_scene();
          queued_for_load = false;
        }
        else if(queued_for_unload)
        {
          unload_scene();
          queued_for_unload = false;
        }
        smap.second->update(dt);
      }

      void scene_manager::load(std::string name)
      {
        queued_scene = name;
        queued_for_load = true;
      }

      void scene_manager::unload()
      {
        queued_for_unload = true;
      }

      void scene_manager::save()
      {
        // get path to save folder
        auto pt = utils::get_game_save_data_folder();
        pt.append("\\scenes");
        pt.append(smap.first);
        std::ofstream stream(pt);
        boost::archive::text_oarchive arch(stream);
        arch << smap;
      }

      void scene_manager::draw() const
      {
        smap.second->draw();
      }

      std::shared_ptr<scene> scene_manager::blank_scene(std::string name)
      {
        std::shared_ptr<scene> sc {new scene(name)};
        smap.first = name;
        smap.second = sc;
        return sc;
      }

      std::shared_ptr<scene> scene_manager::current_scene()
      {
        return smap.second;
      }

      bool scene_manager::operator==(scene_manager const& rhs) const
      {
        return (smap.first == rhs.smap.first) && (*(smap.second) == *(rhs.smap.second));
      }

      void scene_manager::load_scene()
      {
        std::ifstream stream(scene_data[queued_scene]);
        boost::archive::text_iarchive arch(stream);
        arch >> smap;
      }

      void scene_manager::unload_scene()
      {
        smap.first = "";
        smap.second.reset();
      }
    } // namespace impl

    void init()
    {
      // build path to where scene data is stored
      // get scene save data folder
      auto folder = we::utils::get_game_save_data_folder(); // should get us to ..\{user}\%appdata%\roaming\fullhearts
      folder.append("\\scenes"); // move to scene folder
      // get list of files and full paths
      for(auto& f : fs::directory_iterator(folder))
      {
        // save to impl::scene_data
        impl::scene_data[f.path().filename().generic_string()] = f.path();
      }
      if(!impl::smanager)
      {
        impl::smanager = new impl::scene_manager();
      }
      we::log::trace("scenes: init");
    }

    void load(std::string name)
    {
      impl::smanager->load(name);
    }

    void unload()
    {
      impl::smanager->unload();
    }

    void save()
    {
      impl::smanager->save();
    }

    void shutdown()
    {
      we::log::trace("scenes: shutdown");
      delete impl::smanager;
      impl::smanager = nullptr;
    }

    void update(float dt)
    {
      impl::smanager->update(dt);
    }

    void draw()
    {
      impl::smanager->draw();
    }

    std::shared_ptr<scene> current_scene()
    {
      return impl::smanager->current_scene();
    }

    std::shared_ptr<scene> blank_scene(std::string name)
    {
      return impl::smanager->blank_scene(name);
    }
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::scenes::impl::scene_manager);
