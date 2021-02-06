#ifndef _WE_SLIDEFX_HPP_
#define _WE_SLIDEFX_HPP_

#include <chrono>
#include <functional>

#include <glm/glm.hpp>

#include "component.hpp"
#include "timer.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class slidefx : public components::component<slidefx>
    {
    public:
      COMPONENT_REGISTER(slidefx);

      slidefx(std::chrono::milliseconds duration, std::function<glm::vec2(glm::vec2, float)> slide_calculator);
      virtual ~slidefx();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug();

      void start();
      void stop();

    private:
      std::chrono::milliseconds duration_;
      std::function<glm::vec2(glm::vec2, float)> slide_calc_;
      bool running_;
      utils::clock dclk;

    };  
  }
}

#endif