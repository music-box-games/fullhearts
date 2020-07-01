#ifndef _WE_TRANSITION_FADE_HPP_
#define _WE_TRANSITION_FADE_HPP_

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
      class fade_in : public primatives::sized_rectangle
      {
      private:
        void timeup();
        void subtract_alpha(float a);
        utils::machinegun_call mg;
        std::vector<transition_list> queued_transitions;

      public:
        fade_in(std::string const& name, float ms);
        ~fade_in() = default;

        virtual void update(float dt) override;

        fade_in& add_after(transition_list t);
      };
      using fade_in_ptr = std::shared_ptr<fade_in>;

      class fade_out : public primatives::sized_rectangle
      {
      private:
        void timeup();
      public:
        fade_out(std::string const& name, int ms);
        ~fade_out() = default;
      };
      using fade_out_ptr = std::shared_ptr<fade_out>;

      fade_in_ptr build_transition_fadein();
      fade_out_ptr build_transition_fadeout();
    }
  }
}

#endif