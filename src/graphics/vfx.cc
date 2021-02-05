#include "vfx.hpp"
#include "shape.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace vfx
    {
      transition::transition(std::string name) : object_management::gameobject(name), running_(false)
      {

      }

      transition::~transition() {}

      void transition::start()
      {
        running_ = true;
      }

      void transition::stop()
      {
        running_ = false;
      }

      bool transition::running() const
      {
        return running_;
      }

      fade::fade(std::string name, char start_value, char end_value, std::chrono::milliseconds dur) : transition(name), start_alpha(start_value), end_alpha(end_value), duration(dur), the_darkness(rectangle())
      {
        ms_per_1_alpha = std::chrono::milliseconds(duration.count() / (end_alpha - start_alpha));
        the_darkness.set_fill_color(colors::color(0,0,0,start_value));
      }

      fade::~fade() {}

      void fade::start()
      {
        running_ = true;
        duration_clk.restart_ms();
        increment_clk.restart_ms();
      }

      void fade::update(float dt)
      {
        if (!disabled_ && running_)
        {
          std::scoped_lock lock(lock_);

          static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
          std::for_each(components_.begin(), components_.end(), f);
          
          auto ms = increment_clk.restart_ms().count();
          long long add_alpha = ms / ms_per_1_alpha.count();
          colors::color current_color = the_darkness.get_fill_color();
          colors::color new_color = colors::color(current_color.r, current_color.g, current_color.b, current_color.a + add_alpha);
          auto total_ms = duration_clk.get_time_elapsed_ms();
          if(total_ms.count() >= duration.count())
          {
            stop();
          }
        }
      }

      void fade::draw() const
      {
        if (!disabled_ && running_)
        {
          for (auto &c : components_)
          {
            c.second->draw();
            c.second->draw_debug();
          }
        }
        the_darkness.draw(object_transform);
      }
    }
  }
}