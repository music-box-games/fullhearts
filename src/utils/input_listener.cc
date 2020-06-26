#include <functional>

#include "input_listener.hpp"
#include "event_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    input_listener::input_listener(std::string name) : we::object_management::gameobject(name)
    {
      auto f = std::bind(&input_listener::on_input, this, std::placeholders::_1);
      we::events::subscribe<event_subscribe_type>(this, f);
    }

    input_listener::~input_listener()
    {
      we::events::unsubcribe<event_subscribe_type>(this);
    }

    void input_listener::on_input(event_receive_type* ievent)
    {
      func(ievent);
    }

    void input_listener::set_handler(input_handler_type handler)
    {
      func = handler;
    }
  }
}