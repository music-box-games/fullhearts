/******************************************************************************/
/*!
\file   spacemanager.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Space manager class. A space manager is a container for spaces, and handles their
    creation, destruction, updating, and drawing.

*/
/******************************************************************************/

#include <algorithm>

#include <spacemanager.hpp>
#include <space.hpp>

namespace waifuengine
{
namespace object_management
{
space_manager::space_manager() {}
space_manager::~space_manager() {} // shared_ptrs will automatically be deallocated

std::shared_ptr<space> space_manager::add_space(std::string n, space_order o)
{
    auto sp = std::shared_ptr<space>(new space(n, o));
    spaces_[n] = sp;
    return sp;
}

void space_manager::remove_space(std::string n)
{
    spaces_.erase(n);
}

std::shared_ptr<space> space_manager::get_space(std::string n)
{
    return (spaces_.count(n)) ? spaces_[n] : nullptr;
}

void space_manager::update(float dt)
{
    static auto const f = [&dt](std::pair<std::string, std::shared_ptr<space>> sp) -> void { sp.second->update(dt); };
    std::for_each(spaces_.begin(), spaces_.end(), f);
}

void space_manager::draw() const
{
    for (auto &sp : spaces_)
    {
        sp.second->draw();
    }
}

std::size_t space_manager::spaces() const
{
    return spaces_.size();
}

std::size_t space_manager::objects() const
{
    std::size_t count = 0;
    std::for_each(spaces_.begin(), spaces_.end(), [&count](auto sp) {
        count += sp.second->objects();
    });
    return count;
}

std::size_t space_manager::components() const
{
    std::size_t count = 0;
    std::for_each(spaces_.begin(), spaces_.end(), [&count](auto sp) {
        count += sp.second->components();
    });
    return count;
}

void space_manager::clear()
{
    spaces_.clear();
}

void space_manager::remove_object(std::string name)
{
    for (auto &s : spaces_)
    {
        s.second->remove_object(name);
    }
}

bool space_manager::operator==(space_manager const& rhs) const
{
    if(spaces_.size() != rhs.spaces_.size())
    {
        return false;
    }
    
    auto left_iter = spaces_.begin();
    auto right_iter = rhs.spaces_.begin();

    while(left_iter != spaces_.end() && right_iter != rhs.spaces_.end())
    {
        if(!( *((*left_iter).second) == *((*right_iter).second)))
        {
            return false;
        }
        ++left_iter;
        ++right_iter;
    }
    return true;
}

default_spaces space_manager::build_default_spaces()
{
    default_spaces r;
    r.bg = add_space("Background Space", space_order::BACKGROUND);
    r.ch = add_space("Character Space", space_order::CHARACTER);
    r.fx = add_space("FX Space", space_order::FX);
    r.ui = add_space("UI Space", space_order::UI);
    r.tr = add_space("Transition Space", space_order::TRANSITION);
    return r;
}

} // namespace object_management
} // namespace waifuengine

BOOST_CLASS_EXPORT_IMPLEMENT(waifuengine::object_management::space_manager);