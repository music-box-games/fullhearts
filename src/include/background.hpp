#ifndef _WE_BACKGROUND_HPP_
#define _WE_BACKGROUND_HPP_

#include <memory>
#include <unordered_map>

#include "gameobject.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class background : public waifuengine::object_management::gameobject
    {
    private:

    friend class waifuengine::core::debug::imgui_listener;


    
    public:
    background(std::string const& name, std::string const& sprite_name);
      ~background() = default;

      static std::shared_ptr<object_management::gameobject> add_background(std::string const& obj_name, std::string const& sprite_name);

    };
  }
}

#endif