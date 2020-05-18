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

namespace waifuengine
{
namespace object_management
{
namespace impl
{
  static std::unordered_map<std::string, fs::path> object_data;
} // namespace impl

std::unordered_map<std::string, fs::path>& gameobject::get_object_list()
{
  return impl::object_data;
}

void gameobject::update_object_list()
{
  auto pt = we::utils::get_game_save_data_folder().append("objects");
  impl::object_data.clear();
  for(auto& f : fs::directory_iterator(pt))
  {
    impl::object_data[f.path().filename().string()] = f.path();
  }
}

gameobject::gameobject(std::string n) : name_(n) {}
gameobject::~gameobject()
{
  std::scoped_lock lock(lock_);
  components_.clear();
}

void gameobject::update(float dt)
{
  std::scoped_lock lock(lock_);

  static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
  std::for_each(components_.begin(), components_.end(), f);
}

void gameobject::draw() const
{
  for (auto &c : components_)
  {
    c.second->draw();
  }
}

std::string const &gameobject::name() const
{
  return name_;
}

bool gameobject::has_component(std::string name) const
{
  return components_.count(name);
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

void gameobject::save(std::shared_ptr<gameobject> obj)
{
  auto pt = we::utils::get_game_save_data_folder().append("objects");
  pt.append(obj->name_);
  std::ofstream stream(pt);
  boost::archive::text_oarchive arch(stream);
  arch << obj;
}

void gameobject::load(std::shared_ptr<gameobject> obj, std::string name)
{
  auto pt = we::utils::get_game_save_data_folder().append("objects");
  pt.append(name);
  std::ifstream stream(pt);
  boost::archive::text_iarchive arch(stream);
  arch >> obj;
}

} // namespace object_management
} // namespace waifuengine
