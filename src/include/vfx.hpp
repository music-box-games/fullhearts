#ifndef _WE_VFX_HPP_
#define _WE_VFX_HPP_

#include <chrono>

#include "gameobject.hpp"
#include "debug.hpp"
#include "timer.hpp"
#include "timer_manager.hpp"
#include "rectangle.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace vfx
    {
      class transition : public object_management::gameobject
      {
      public:
        transition(std::string name);
        virtual ~transition();
        void start();
        void stop();

        bool running() const;

      protected:
        bool running_;

      private:
        friend class core::debug::imgui_listener;
      };

      class fade : public transition
      {
      public:
        fade(std::string name, int start_value, int end_value, std::chrono::milliseconds duration);
        ~fade();

        virtual void start();

        void update(float dt);
        void draw() const;

      private:
        friend class core::debug::imgui_listener;
        int start_alpha;
        int end_alpha;
        int curr_alpha;
        std::chrono::milliseconds duration;
        utils::clock duration_clk;
        utils::clock increment_clk;
        float ms_per_1_alpha;
        rectangle the_darkness;
      };
    }
  }
}

#endif