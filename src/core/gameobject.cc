/******************************************************************************/
/*!
\file   gameobject.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Game object class. The game object works as a container for components.

*/
/******************************************************************************/

#include <gameobject.hpp>
#include <component.hpp>
#include <dummy.hpp>

namespace waifuengine
{
namespace object_management
{
gameobject::gameobject(std::string n) : name_(n) {}
gameobject::~gameobject()
{
  std::scoped_lock(lock_);
  components_.clear();
}

void gameobject::update(float dt)
{
  std::scoped_lock(lock_);

  static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
  std::for_each(components_.begin(), components_.end(), f);
}

void gameobject::draw() const
{
  std::scoped_lock(lock_);
  for (auto &c : components_)
  {
    c.second->draw();
  }
}

std::string const &gameobject::name() const
{
  std::scoped_lock(lock_);

  return name_;
}

bool gameobject::operator==(gameobject const &rhs)
{
  return (components_ == rhs.components_) && (name_ == rhs.name_);
}

void gameobject::register_components_with_archive(boost::archive::text_oarchive& ar)
{
  using namespace waifuengine::components;
  ar.template register_type<component<dummy>>();
}

void gameobject::register_components_with_archive(boost::archive::text_iarchive& ar)
{
  using namespace waifuengine::components;
  ar.template register_type<component<dummy>>();
}

} // namespace object_management
} // namespace waifuengine
