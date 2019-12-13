#ifndef _W_ARGS_HPP_
#define _W_ARGS_HPP_

#include <optional>

namespace waifuengine
{
  namespace utils
  {
    namespace args
    {
      enum return_values
      {
        gtest_success,
        gtest_fail,
        hardware_dump,
      };

      std::optional<int> parse(int argc, char ** argv);
    }
  }
}

#endif // _W_ARGS_HPP_