#include <algorithm>

#include "polygon.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    polygon::polygon(std::initializer_list<line2d> lines)
    {
      for(auto l : lines)
      {
        sides.push_back(l);
      }      
    }

    polygon::~polygon() {}

    void polygon::draw(colors::rgba_value c)
    {
      // auto shdopt = shaders::get_shader("debug_line_shader");
      // std::shared_ptr<shaders::shader> shd;
      // if(shdopt.has_value())
      // {
      //   shd = shdopt.value();
      // }
      // else{
      //   // TOOD: error handle
      // }

      // shd->use(); // use shader

      // // calc size of vertex array
      // std::size_t vert_array_size = sides.size() * 2;
      // std::vector<float> verts;
      // verts.reserve(vert_array_size);
      // for(auto const& s : sides)
      // {
      //   verts.push_back(s.start.x);
      //   verts.push_back(s.start.y);
      //   verts.push_back(s.end.x);
      //   verts.push_back(s.end.y);
      // }

      // shd->set_float_3("color", c.r, c.g, c.b);
      // shd->set_float_1("alpha", c.a);

      // glBindVertexArray(VAO);
      // glBindBuffer(GL_ARRAY_BUFFER, VBO);
      // glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

      // int position_attribute = shd->get_attribute("position");
      // glEnableVertexAttribArray(position_attribute);
      // glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

      // glDrawArrays(GL_LINES, 0, vert_array_size);
      for(auto& s : sides)
      {
        s.draw(colors::rgb_value(c.r, c.g, c.b), c.a);
      }
    }
  }
}