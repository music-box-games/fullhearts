#ifndef _WE_BUTTON_COLLIDER_HPP_
#define _WE_BUTTON_COLLIDER_HPP_

#include <functional>

#include <collider.hpp>
#include <input_event.hpp>
#include <SDL.h>

namespace waifuengine
{
  namespace physics
  {
    class button_collider : public collider
    {
    public:
      COMPONENT_NAME(buton_collider);
      COMPONENT_TYPE(button_collider);

      button_collider();
      virtual ~button_collider();

      virtual void update(float dt);
      virtual void draw() const;

      void set_trigger(std::function<void()> func);

      void set_nonhover_image(std::string name);
      void set_hover_image(std::string name);

    private:
      void input_handler(waifuengine::events::event* e);
      bool check_point_collision(int const& x, int const& y);
      void get_line(int line, int* x1, int* y1, int* x2, int* y2) const;
      bool hover;
      std::string nhimage, himage;
      std::function<void()> f;
    };
  }
}

#endif