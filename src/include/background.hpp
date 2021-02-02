
#ifndef _WE_BACKGROUND_HPP_
#define _WE_BACKGROUND_HPP_

#include "gameobject.hpp"
#include "filesystem.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class background : public ::we::object_management::gameobject
    {
    private:
      friend class waifuengine::core::debug::imgui_listener;
    public:
      background(std::string n = "", fs::path texture_file = "default");
      virtual ~background() = default;
    };
  }
}

#endif