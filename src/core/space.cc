/******************************************************************************/
/*!
\file   space.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Space class. A space is a container for gameobjects, and handles the creation,
    destruction, updating, and drawing of game objects.

*/
/******************************************************************************/

#include <algorithm>
#include <numeric>

#include <space.hpp>
#include <gameobject.hpp>


// TODO: a lot of the allocation functions are going to have to change upon custom memory management

namespace waifuengine
{
    namespace object_management
    {
        space::space(std::string n, space_order o) : name_(n), order_(o)
        {

        }

        space::~space()
        {
            // remove all objects from map
            objects_.clear();
        }

        std::shared_ptr<gameobject> space::add_object(std::string n)
        {
            // add object and place it in the map
            auto obj = std::shared_ptr<gameobject>(new gameobject(n));
            objects_[n] = obj;
            return obj;
        }

        void space::remove_object(std::string n)
        {
            objects_.erase(n);
        }

        std::shared_ptr<gameobject> space::get_object(std::string n)
        {
            return (objects_.count(n)) ? objects_[n] : nullptr;
        }

        void space::update(float dt)
        {
            static auto const f = [&dt](std::pair<std::string, std::shared_ptr<gameobject>> obj) -> void { obj.second->update(dt); };
            std::for_each(objects_.begin(), objects_.end(), f);
        }

        void space::draw() const
        {
          for (auto& obj : objects_)
          {
            obj.second->draw();
          }
        }

        std::size_t space::objects() const
        {
            return objects_.size();
        }

        std::size_t space::components() const
        {
            std::size_t count = 0;
            std::for_each(objects_.begin(), objects_.end(), [&count](auto obj) {
                count += obj.second->components();
            });
            return count;
        }

        bool space::operator<(space const& rhs) const
        {
          return order_ < rhs.order_;
        }
    }
}
