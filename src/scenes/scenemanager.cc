/******************************************************************************/
/*!
\file   scenemanager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  The scene manager manages all existing scenes.

*/
/******************************************************************************/

#include <scenemanager.hpp>

#include <log.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    namespace impl
    {
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
        smap.second->update(dt);
      }

      void scene_manager::draw() const
      {
        smap.second->draw();
      }

      std::shared_ptr<scene> scene_manager::current_scene()
      {
        return smap.second;
      }
    }

    void init()
    {
      if(!impl::smanager)
      {
        impl::smanager = new impl::scene_manager();
      }
      we::log::trace("scenes: init");
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
  }
}