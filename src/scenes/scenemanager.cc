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

      std::unordered_map<std::string, fs::path>& scene_manager::get_scene_list()
      {
        return scene_data;
      }

      void scene_manager::update_scene_saves()
      {
        scene_data.clear(); // TODO: can probably be optimized
        auto folder = we::utils::get_game_save_data_folder().append("scenes");
        for(auto& f : fs::directory_iterator(folder))
        {
          scene_data[f.path().filename().string()] = f.path();
        }
      }

      void scene_manager::queue_scene(std::function<void()> sl)
      {
        scene_loader = sl;
        queued_for_load = true;
      }

      scene_manager::scene_manager() : smap({})
      {
        we::log::trace("scene manager construction");
        // navigate to the scenes save data folder and check for existing archives
        // add them to impl::scene_data if found, then update on each loop
        update_scene_saves();
      }

      scene_manager::~scene_manager()
      {
        we::log::trace("scene manager destruction");
      }

      void scene_manager::update(float dt)
      {
        update_scene_saves();
        we::object_management::gameobject::update_object_list();
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
        if (smap.second.use_count())
        {
          smap.second->update(dt);
        }
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
        pt.append("scenes");
        pt.append(smap.first);
        std::ofstream stream(pt.string());
        boost::archive::text_oarchive arch(stream);
        arch << smap;
      }

      void scene_manager::draw() const
      {
        if (smap.second.use_count())
        {
          smap.second->draw();
        }
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
        scene_loader();
      }

      void scene_manager::unload_scene()
      {
        smap.first = "";
        smap.second.reset();
      }
    } // namespace impl

    void init()
    {
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

    void queue_scene(std::function<void()> sl)
    {
      impl::smanager->queue_scene(sl);
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
  } // namespace scenes
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::scenes::impl::scene_manager);
