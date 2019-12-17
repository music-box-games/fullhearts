#include <basic_shape.hpp>

namespace waifuengine
{
  namespace components
  {
    basic_shape::basic_shape() : component<basic_shape>() {}
    basic_shape::~basic_shape() {}

    basic_triangle::basic_triangle() : basic_shape(), vertbuffer()
    {
      glGenBuffers(1, &vertbuffer); // generate the buffer
      // bind buffer to array buffer
      glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
      // pass vertices to opengl
      glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }

    basic_triangle::~basic_triangle() 
    {

    }

    void basic_triangle::update(float)
    {

    }

    void basic_triangle::draw() const
    {
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
      glVertexAttribPointer(
        0, // no purpose but must match shader
        3, // size
        GL_FLOAT, // vertice data type
        GL_FALSE, // normalized data?
        0, // stride
        (void*)0 // array buffer offset
      );
      // finally draw
      glDrawArrays(GL_TRIANGLES, 0, 3); // draw from vert 0 -> vert 3 aka triangle
      glDisableVertexAttribArray(0);
    }
  }
}