#include "text.hpp"
#include "graphics.hpp"

namespace waifuengine
{
  namespace graphics
  {
    text::text() : style_(static_cast<int>(text::style::regular)) {}
    text::text(std::string s) : style_(static_cast<int>(text::style::regular)), tstr_(s) {}
    text::~text() {}

    void text::set_font(std::string font_name)
    {
      fontname_ = font_name;
      tobj_.setFont(graphics::get_font_manager().lock()->get_font(font_name).value()->data());
    }

    void text::set_char_size_in_pixels(int sz)
    {
      tobj_.setCharacterSize(sz);
    } 

    void text::set_fill_color_idle(colors::color c)
    {
      idle_fill_color_ = c;
    }

    void text::set_fill_color_hover(colors::color c)
    {
      hover_fill_color_ = c;
    }

    void text::set_fill_color_inactive(colors::color c)
    {
      inactive_fill_color_ = c;
    }

    void text::set_active_color(colors::color c)
    {
      current_color_ = c;
      tobj_.setFillColor(colors::convert_we_color_to_sfml_color(c));
    }

    void text::set_style(int st)
    {
      style_ = st;
      tobj_.setStyle(st);
    }

    void text::set_string(std::string s)
    {
      tstr_ = s;
      tobj_.setString(s);
    }

    std::string text::get_font() const
    {
      return fontname_;
    }

    int text::get_char_size_in_pixels() const
    {
      return tobj_.getCharacterSize();
    }

    colors::color text::get_active_color() const
    {
      return current_color_;
    }

    colors::color text::get_fill_color_hover() const
    {
      return hover_fill_color_;
    }

    colors::color text::get_fill_color_idle() const
    {
      return idle_fill_color_;
    }

    colors::color text::get_fill_color_inactive() const
    {
      return inactive_fill_color_;
    }

    int text::get_style() const
    {
      return style_;
    }

    std::string text::get_string() const
    {
      return tstr_;
    }

    sf::Text& text::data()
    {
      return tobj_;
    }

    sf::Text const& text::data() const
    {
      return tobj_;
    }
  }
}
