#ifndef _W_RETURN_VALUES_HPP_
#define _W_RETURN_VALUES_HPP_

namespace waifuengine
{
  namespace core
  {
      enum return_values
      {
        glfw_fail_init = -1,
        glfw_window_fail = -2,

        help = 1,
        gtest_success,
        gtest_fail,
        hardware_dump,
      };
  }
}

#endif