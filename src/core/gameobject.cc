/******************************************************************************/
/*!
\file   gameobject.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Game object class. The game object works as a container for components.

*/
/******************************************************************************/

#include <sstream>
#include <iostream>

#include <gameobject.hpp>
#include <component.hpp>
#include <dummy.hpp>
#include <utils.hpp>
#include "log.hpp"
#include "sprite.hpp"

namespace waifuengine
{
  namespace object_management
  {
    namespace impl
    {
      static std::unordered_map<std::string, fs::path> object_data;
    } // namespace impl

    graphics::transform& gameobject::get_transform()
    {
      return object_transform;
    }

    void gameobject::set_transform(graphics::transform const &tr)
    {
      object_transform = tr;
    }

    std::unordered_map<std::string, fs::path> &gameobject::get_object_list()
    {
      return impl::object_data;
    }

    void gameobject::update_object_list()
    {
      auto pt = we::utils::get_game_save_data_folder().append("objects");
      impl::object_data.clear();
      for (auto &f : fs::directory_iterator(pt))
      {
        impl::object_data[f.path().filename().string()] = f.path();
      }
    }

    gameobject::gameobject(std::string n) : name_(n), disabled_(false), object_transform({})
    {
      waifuengine::log::LOGTRACE(std::string("Constructing gameobject: " + n));
    }

    gameobject::~gameobject()
    {
      std::scoped_lock lock(lock_);
      waifuengine::log::LOGTRACE(std::string("Destructing gameobject: " + name_));
      components_.clear(); // delete components
      // transform component is auto-magically deleted
    }

    void gameobject::update(float dt)
    {
      if (!disabled_)
      {

        std::scoped_lock lock(lock_);

        static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
        std::for_each(components_.begin(), components_.end(), f);
      }
    }

    void gameobject::draw() const
    {
      if (!disabled_)
      {
        for (auto &c : components_)
        {
          c.second->draw();
          c.second->draw_debug();
        }
      }
    }

    std::string const &gameobject::name() const
    {
      return name_;
    }

    bool gameobject::has_component(std::string name) const
    {
      // TODO: un hard code this
      return (name == "transform") ? true : components_.count(name);
    }

    bool gameobject::operator==(gameobject const &rhs)
    {
      if (name_ != rhs.name_)
      {
        return false;
      }
      if (components_.size() != rhs.components_.size())
      {
        return false;
      }
      if(object_transform != rhs.object_transform)
      {
        return false;
      }

      auto left_iter = components_.begin();
      auto right_iter = rhs.components_.begin();

      while (left_iter != components_.end() && right_iter != rhs.components_.end())
      {
        if (!(*((*left_iter).second) == *((*right_iter).second)))
        {
          return false;
        }
        ++left_iter;
        ++right_iter;
      }
      return true;
    }

    std::string gameobject::dump() const
    {
      std::stringstream ss;
      ss << "Gameobject: " << name_ << '\n';
      ss << "Number of components: " << components_.size() << '\n';
      for (auto &pair : components_)
      {
        ss << '\t' << pair.first << '\n';
      }
      return ss.str();
    }

    void gameobject::disable(bool set)
    {
      disabled_ = set;
    }

    bool gameobject::disabled() const
    {
      return disabled_;
    }

    void gameobject::save(std::shared_ptr<gameobject> )
    {

    }

    void gameobject::load(std::shared_ptr<gameobject> , std::string )
    {

    }

    void gameobject::rotate(float r)
    {
      object_transform.rotate(r);
    }
    // TODO: find a better way to call it on all applicable components
    void gameobject::set_rotation(float r)
    {
      object_transform.set_rotation(r);
    }

    void gameobject::translate(glm::vec2 t)
    {
      object_transform.translate(t);
    }

    void gameobject::set_translation(glm::vec2 p)
    {
      object_transform.set_translation(p);
    }

    void gameobject::scale(glm::vec2 s)
    {
      object_transform.scale(s);
    }

    void gameobject::set_scale(glm::vec2 s)
    {
      object_transform.set_scale(s);
    }

  } // namespace object_management
} // namespace waifuengine
