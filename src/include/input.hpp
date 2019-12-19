/******************************************************************************/
/*!
\file   input.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Handles user input.

*/
/******************************************************************************/

#ifndef _W_INPUT_HPP_
#define _W_INPUT_HPP_

namespace waifuengine
{
  namespace input
  {
    namespace opengl
    {
      void init();
      void update();
      void shutdown();
    }

    void init();
    void update();
    void shutdown();
  }
}

#endif // _W_INPUT_HPP_