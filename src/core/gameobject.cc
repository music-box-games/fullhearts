
#include <gameobject.hpp>
#include <component.hpp>

namespace waifuengine
{
    namespace object_management
    {
        gameobject::gameobject(std::string n) : name_(n) {}
        gameobject::~gameobject() {}

        void gameobject::update(float dt)
        {
            static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt);};
            std::for_each(components_.begin(), components_.end(), f);
        }  

        void gameobject::draw() const
        {
            static auto const f = [](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->draw();};
            std::for_each(components_.begin(), components_.end(), f);
        }

        std::string const& gameobject::name() const
        {
            return name_;
        }
    }
}
