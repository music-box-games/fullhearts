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
#include <physics.hpp>

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
  if(name_ != rhs.name_)
  {
    return false;
  }
  if(components_.size() != rhs.components_.size())
  {
    return false;
  }
  auto left_iter = components_.begin();
  auto right_iter = rhs.components_.begin();

  while(left_iter != components_.end() && right_iter != rhs.components_.end())
  {
    if(!(*((*left_iter).second) == *((*right_iter).second)))
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

std::string gameobject::get_error() const
{
  return error_;
}

} // namespace object_management
} // namespace waifuengine
