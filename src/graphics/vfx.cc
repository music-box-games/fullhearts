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

      fade::fade(std::string name, int start_value, int end_value, std::chrono::milliseconds dur) : transition(name), start_alpha(start_value), end_alpha(end_value), curr_alpha(255), duration(dur), the_darkness(rectangle())
      {
        // takes this many ms to change 1 alpha on the image
        ms_per_1_alpha = std::chrono::milliseconds(std::abs(duration.count() / (end_alpha - start_alpha))).count();
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
          
          auto ms_elapsed = increment_clk.get_time_elapsed_ms().count(); // ms since last fade::update
          long long add_alpha = (ms_elapsed / ms_per_1_alpha); // how many alpha to add/subtract from the current value
          colors::color curcolor = the_darkness.get_fill_color(); // current color of the rectangle making the fade effect
          colors::color new_color = curcolor;
          if(ms_elapsed > ms_per_1_alpha)
          {
            // if fading in
            if(start_alpha > end_alpha)
            {
              new_color.a = new_color.a - add_alpha;
            }
            else if(start_alpha < end_alpha)
            {
              new_color.a = new_color.a + add_alpha;
            }
            the_darkness.set_fill_color(new_color);
            increment_clk.restart_ms();
          }
          curr_alpha = new_color.a; 

          // check total fade duration
          auto total_ms = duration_clk.get_time_elapsed_ms();
          if(total_ms.count() >= duration.count())
          {
            // todo: send a warning instead of this happening silently
            if(curr_alpha != end_alpha)
            {
              auto c = the_darkness.get_fill_color();
              c.a = end_alpha;
              the_darkness.set_fill_color(c);
              curr_alpha = end_alpha;
            }
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