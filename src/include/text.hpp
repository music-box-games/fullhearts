#ifndef _WE_TEXT_HPP_
#define _WE_TEXT_HPP_

#include <SFML/Graphics.hpp>

#include "graphics.hpp"
#include "font_manager.hpp"
#include "colors.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class text
    {
    public:
      enum class style : int
      {
        regular       = 0,
        bold          = 1 << 0,
        italic        = 1 << 1,
        underlined    = 1 << 2,
        strikethrough = 1 << 3,
      };

      text();
      text(std::string s);
      ~text();

      void set_font(std::string font_name);
      void set_char_size_in_pixels(int sz);
      void set_active_color(colors::color c);
      void set_fill_color_idle(colors::color c);
      void set_fill_color_hover(colors::color c);
      void set_fill_color_inactive(colors::color c);
      void set_style(int st);
      void set_string(std::string s); // TODO: wide strings

      std::string get_font() const;
      int get_char_size_in_pixels() const;
      colors::color get_active_color() const;
      colors::color get_fill_color_idle() const;
      colors::color get_fill_color_hover() const;
      colors::color get_fill_color_inactive() const;
      int get_style() const;
      std::string get_string() const; 

      sf::Text& data();
      sf::Text const& data() const;

    private:
      friend class core::debug::imgui_listener;
      int style_;
      sf::Text tobj_;
      colors::color current_color_;
      colors::color idle_fill_color_;
      colors::color hover_fill_color_;
      colors::color inactive_fill_color_;
      std::string tstr_;
      std::string fontname_;
    };
  }
}

#endif