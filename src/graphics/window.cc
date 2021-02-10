#include "window.hpp"
#include "event_manager.hpp"
#include "input_event.hpp"
#include <imgui-SFML.h>

namespace waifuengine
{
  namespace graphics
  {
    window::window(int w, int h, std::string t) : width_(w), height_(h), title_(t)
    {
      rw = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width_, height_), title_));
    }

    window::~window()
    {
      rw->close();
    }

    void window::clear()
    {
      rw->clear();
    }

    void window::display()
    {
      rw->display();
    }

    void window::set_frame_limit(int f)
    {
      rw->setFramerateLimit(f);
    }

    glm::vec2 window::get_dimensions() const
    {
      sf::Vector2u s = rw->getSize();
      return glm::vec2(s.x, s.y);
    }

    void window::update()
    {
      // events
      sf::Event ev;
      while(rw->pollEvent(ev))
      {
        ImGui::SFML::ProcessEvent(ev);
        // handle events, convert them into engine events
        if(ev.type == sf::Event::EventType::Closed)
        {
          events::send_shutdown_event();
        }
        else if(ev.type == sf::Event::EventType::KeyPressed)
        {
          input::input_event ie(input::from_api_key(ev.key.code), input::actions::press);
          events::handle(&ie);
        }
        else if(ev.type == sf::Event::EventType::KeyReleased)
        {
          input::input_event ie(input::from_api_key(ev.key.code), input::actions::release);
          events::handle(&ie);
        }
      }
    }

    std::weak_ptr<sf::RenderWindow> window::data()
    {
      return rw;
    }
  }
}