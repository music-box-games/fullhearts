#ifndef _WE_TRANSITION_FADE_HPP_
#define _WE_TRANSITION_FADE_HPP_

#include <vector>

#include "gameobject.hpp"
#include "timer_manager.hpp"
#include "timer.hpp"
#include "graphics_primatives.hpp"
#include "machinegun_call.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      enum class transition_list;

      

      class fade_in : public primatives::rectangle
      {
      private:
        void timeup();
        void subtract_alpha(float a);
        utils::machinegun_call mg;
        std::vector<transition_list> queued_transitions;
        std::function<void()> post_transition_script;

      public:
        fade_in(std::string const& name, float ms);
        virtual ~fade_in() = default;
        virtual void update(float dt) override;
        fade_in& add_after(transition_list t);
        fade_in& add_post_transition_script(std::function<void()> s);
      };
      using fade_in_ptr = std::shared_ptr<fade_in>;

      class fade_out : public primatives::rectangle
      {
      private:
        void timeup();
        void add_alpha(float a);
        utils::machinegun_call mg;
        std::vector<transition_list> queued_transitions;
      public:
        fade_out(std::string const& name, int ms);
        virtual ~fade_out() = default;

        virtual void update(float dt) override;
        fade_out& add_after(transition_list t);
      };
      using fade_out_ptr = std::shared_ptr<fade_out>;

      fade_in_ptr build_transition_fadein(int length_ms);
      fade_out_ptr build_transition_fadeout(int length_ms);
    }
  }
}

#endif