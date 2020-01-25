/******************************************************************************/
/*!
\file   graphics.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Graphics namespaces. Handles the initialization and shutdown of graphics systems
  and various APIs.

*/
/******************************************************************************/

#ifndef _W_GRAPHICS_HPP_
#define _W_GRAPHICS_HPP_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window.hpp>

namespace waifuengine
{
  namespace graphics
  {
    void init(unsigned width, unsigned height, std::string title);
    void clear();
    void render();
    void shutdown();
    std::shared_ptr<window> get_window();
  }
}

#endif // !_W_GRAPHICS_HPP_