/******************************************************************************/
/*!
\file   args.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Handles parsing arguments passed into the program.

*/
/******************************************************************************/

#ifndef _W_ARGS_HPP_
#define _W_ARGS_HPP_

#include <optional>

#include <return_values.hpp>

namespace waifuengine
{
  namespace utils
  {
    namespace args
    {
      std::optional<int> parse(int argc, char ** argv);
    }
  }
}

#endif // _W_ARGS_HPP_