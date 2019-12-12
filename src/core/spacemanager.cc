#include <algorithm>

#include <spacemanager.hpp>
#include <space.hpp>

namespace waifuengine
{
    namespace object_management
    {
        space_manager::space_manager() {}
        space_manager::~space_manager() {} // shared_ptrs will automatically be deallocated

        std::shared_ptr<space> space_manager::add_space(std::string n)
        {
            auto sp = std::shared_ptr<space>(new space(n));
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
            static auto const f = [](std::pair<std::string, std::shared_ptr<space>> sp) -> void { sp.second->draw(); };
            std::for_each(spaces_.begin(), spaces_.end(), f);
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

    }
}