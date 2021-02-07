#include "slidefx.hpp"
#include "gameobject.hpp"

namespace waifuengine
{
  namespace graphics
  {
    slidefx::slidefx(std::chrono::milliseconds dur, std::function<glm::vec2(glm::vec2, float)> slidcalc) : components::component<slidefx>(), duration_(dur), slide_calc_(slidcalc), running_(false) {}
    slidefx::~slidefx() {}

    void slidefx::update(float dt)
    {
      if(running_)
      {
        if(dclk.get_time_elapsed_ms().count() >= duration_.count())
        {
          stop();
        }
        glm::vec2 new_pos = slide_calc_(parent->get_transform().translation(), dt * 1000);
        parent->set_translation(new_pos);
      }
    }

    void slidefx::draw() const
    {

    }

    void slidefx::draw_debug()
    {

    }

    void slidefx::start()
    {
      running_ = true;
      dclk.restart_ms();
    }

    void slidefx::stop()
    {
      running_ = false;
    }
  }
}