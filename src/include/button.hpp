#ifndef _WE_BUTTON_HPP_
#define _WE_BUTTON_HPP_

#include <SFML/Graphics.hpp>

#include "gameobject.hpp"
#include "colors.hpp"
#include "text.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace ui
  {
    class button : public object_management::gameobject
    {
    private:
      friend class core::debug::imgui_listener;


    public:
      button(std::string const& name, std::optional<fs::path> texture_file);
      virtual ~button();
    };

    class text_button : public button
    {
    private:
      friend class core::debug::imgui_listener;
      graphics::text tobj_;
      
    public:
      text_button(std::string const& name, std::optional<fs::path> button_texture, std::string text = "");
      virtual ~text_button();

      void set_font(std::string font_name);
      void set_color(graphics::colors::color c);
      void set_char_size_in_pixels(int size);
      void set_string(std::string s);
      void set_style(int st);

      virtual void update(float dt);
      virtual void draw() const;
    };

  }
}

#endif