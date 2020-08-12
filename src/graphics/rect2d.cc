#include <boost/container_hash/hash.hpp>

#include "rect2d.hpp"
#include "graphics.hpp"
#include "shader.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    rect2d::rect2d(line2d a, line2d b, line2d c, line2d d) : VAO(0), VBO(0), EBO(0)
    {
      sides[0] = a;
      sides[1] = b;
      sides[3] = c;
      sides[4] = d;

                    glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    void rect2d::draw(glm::vec3 color, float alpha)
    {
      auto shdopt = shaders::get_shader("debug_line_shader");
      std::shared_ptr<shaders::shader> shd;
      if(shdopt.has_value())
      {
        shd = shdopt.value();
      }
      else{
        // TOOD: error handle
      }
      shd->use();
      std::array<float, 8> verts = {
        sides[0].start.x, sides[0].start.y,
        sides[1].start.x, sides[1].start.y,
        sides[2].start.x, sides[2].start.y,
        sides[3].start.x, sides[3].start.y,
                    };
      unsigned int elements[] = {0, 1, 2, 2, 3, 0};

      shd->set_float_3("color", color.r, color.g, color.b);
      shd->set_float_1("alpha", alpha);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

      int position_attribute = shd->get_attribute("position");
      glEnableVertexAttribArray(position_attribute);
      glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
    }

    bool rect2d::operator==(rect2d const& rhs) const
    {
      return (sides[0] == rhs.sides[0]) &&
      (sides[1] == rhs.sides[1]) &&
      (sides[2] == rhs.sides[2]) &&
      (sides[3] == rhs.sides[3]);     
    }
  }
}

namespace std
{
  template<>
  struct hash<we::graphics::rect2d>
  {
    std::size_t operator()(we::graphics::rect2d const& r)
    {
      std::size_t seed = 0;
      
    }
  };
}