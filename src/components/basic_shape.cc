/******************************************************************************/
/*!
\file   basic_shape.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  A collection of classes that draw basic shapes.

*/
/******************************************************************************/

#include <cmath>

#include <basic_shape.hpp>

#include <log.hpp>
#include <graphics.hpp>
#include <shader.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace components
  {
    basic_shape::basic_shape() : component<basic_shape>() {}
    basic_shape::~basic_shape() {}

    basic_triangle::basic_triangle() : basic_shape()
    {
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glBindVertexArray(vao);

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }

    basic_triangle::~basic_triangle() 
    {

    }

    void basic_triangle::update(float)
    {
      // TODO: find a better way to fade between colors
      we::log::pedantic("basic_triangle: update");
      float timevalue = glfwGetTime(); // TODO: maybe move the calculations to the shader
      float redvalue = (std::cos(timevalue) / 2.0f) + 0.5f;
      float greenvalue = (std::sin(timevalue) / 2.0f) + 0.5f;
      float bluevalue = (std::acos(timevalue)) + 0.5f;
      we::graphics::shaders::shader shd = we::graphics::opengl::shader_id();
      shd.use();
      shd.set_uniform4<float>("tricolor", redvalue, greenvalue, bluevalue, 1.0f);
    }

    void basic_triangle::draw() const
    {
      we::log::pedantic("basic_triangle: draw");
      we::graphics::opengl::shader_id().use();
      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
  }
}