#ifndef _WE_INPUT_HPP_
#define _WE_INPUT_HPP_

#include <unordered_map>

#include <events.hpp>
#include <window.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace input
    {
      void process();

      enum class key
      {
        space,
        apostrophe,
        comma,
        minus,
        period,
        slash,
        zero,one,two,three,four,five,six,seven,eight,nine,
        semicolon,
        equal,
        a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
        left_bracket, backslash, right_bracket, grave_accent,
        world_1, world_2,
        escape,
        enter,
        tab,
        backspace,
        insert,
        del,
        right,
        left,
        down,
        up,
        page_up,
        page_down,
        home,
        end,
        caps_lock,
        scroll_lock,
        num_lock,
        print_screen,
        pause,
        f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
        f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25,
        kp_0, kp_1, kp_2, kp_3, kp_4, kp_5, kp_6, kp_7, kp_8, kp_9,
        kp_decimal, kp_divide, kp_multiply, kp_subtract, kp_add, 
        kp_enter, kp_equal,
        left_shift, left_control, left_alt, left_super,
        right_shift, right_control, right_alt, right_super,
        menu, 

        // special 
        Default,
      };

      enum class action
      {
        press,
        release,
        Default,
      };

      namespace impl
      {
        extern std::unordered_map<decltype(GLFW_KEY_UNKNOWN), key> keyset;
        extern std::unordered_map<decltype(GLFW_PRESS), action> actionset;
      }

      class input_event : public waifuengine::events::event
      {
      public:
        EVENT_NAME(input_event);

        input_event();
        input_event(key, action, window_id_type);
        ~input_event();

        key k;
        action a;
        waifuengine::graphics::window_id_type w;
      };
    }
  }
}

#endif