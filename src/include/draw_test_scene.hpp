/******************************************************************************/
/*!
\file   draw_test_scene.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Test scene for testing drawing.

*/
/******************************************************************************/

#ifndef _WE_DRAW_TEST_SCENE_HPP_
#define _WE_DRAW_TEST_SCENE_HPP_

#include <scenes.hpp>

namespace waifuengine
{
  namespace scenes
  {
    class draw_test_scene : public scene 
    {
    private:
    public:
      SCENE_NAME(draw_test_scene);

      draw_test_scene();
      virtual ~draw_test_scene();
    };
  }
}

#endif // !_WE_DRAW_TEST_HPP_