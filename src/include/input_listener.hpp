#ifndef _WE_INPUT_LISTENER_HPP_
#define _WE_INPUT_LISTENER_HPP_

#include "gameobject.hpp"
#include "input.hpp"
#include "events.hpp"

namespace waifuengine
{
  namespace utils
  {
    class input_listener : public ::waifuengine::object_management::gameobject
    {
    public:
      typedef waifuengine::events::event event_receive_type;
      typedef waifuengine::graphics::input::input_event event_subscribe_type;
      typedef std::function<void(event_receive_type*)> input_handler_type;
    private:
      input_handler_type func;

      void on_input(event_receive_type* ievent);

    public:
      input_listener(std::string name);
      virtual ~input_listener();

      void set_handler(input_handler_type f);
    };
  } // namespace utils
} // namespace waifuengine

#endif