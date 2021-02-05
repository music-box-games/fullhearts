#ifndef _WE_FONT_MANAGER_HPP_
#define _WE_FONT_MANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <optional>

#include "font.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class font_manager
    {
    public:
      font_manager();
      ~font_manager();

      std::optional<std::shared_ptr<font>> load_font(std::string name, std::string filename);
      void unload_font(std::string name);
      std::optional<std::shared_ptr<font>> get_font(std::string name);
      bool has_font(std::string name) const;
      int count() const;

    private:
      friend class core::debug::imgui_listener;
      std::unordered_map<std::string, std::shared_ptr<font>> fonts_;
    };
  }
}

#endif