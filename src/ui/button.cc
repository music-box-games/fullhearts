#include <sstream>

#include "button.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "window.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "transform.hpp"
#include "log.hpp"
#include "graphics.hpp"
#include "font_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace ui
  {
    button::button(std::string const& name, std::optional<fs::path> texture_file) : object_management::gameobject(name)
    {
      if(texture_file.has_value())
      {
        add_component_v<graphics::sprite>(texture_file.value());
      }
    }

    button::~button()
    {
    }

    text_button::text_button(std::string const& name, std::optional<fs::path> button_texture, std::string text) : button(name, button_texture), tobj_(graphics::text(text))
    {

    }

    text_button::~text_button() {}
    
    void text_button::set_font(std::string font_name)
    {
      tobj_.set_font(font_name);
    }

    void text_button::set_color(graphics::colors::color c)
    {
      tobj_.set_active_color(c);
    }

    void text_button::set_char_size_in_pixels(int sz)
    {
      tobj_.set_char_size_in_pixels(sz);
    }

    void text_button::set_string(std::string s)
    {
      tobj_.set_string(s);
    }

    void text_button::set_style(int st)
    {
      tobj_.set_style(st);
    }

    void text_button::draw() const
    {
      if (!disabled_)
      {
        for (auto &c : components_)
        {
          c.second->draw();
          c.second->draw_debug();
        }
        // draw text after components
        graphics::get_window_manager().lock()->get_main_window().lock()->data().lock()->draw(tobj_.data(), sf::RenderStates(object_transform.data().getTransform()));
      }
    }

  }
}