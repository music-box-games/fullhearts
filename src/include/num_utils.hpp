#ifndef _WE_NUM_UTILS_HPP_
#define _WE_NUM_UTILS_HPP_

namespace waifuengine
{
  namespace utils
  {
    template<typename T>
    T clamp(T bot, T top, T value)
    {
      if(value < bot) return bot;
      if(value > top) return top;
      else return value;
    }
  }
}

#endif