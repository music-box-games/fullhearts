
#include <boost/container_hash/hash.hpp>

#include <array>

#include "line2d.hpp"
#include "shader.hpp"
#include "graphics.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    line2d::line2d(point_2d s, point_2d e) : start(s), end(e)
    {
              glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    line2d::line2d() : start(glm::vec2(0.f, 0.f)), end(glm::vec2(0.f, 0.f))
    {
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);
    }

    line2d::~line2d() {}

    void line2d::draw(glm::vec3 color, float alpha)
    {
      auto shdopt = shaders::get_shader("line_shader");
      std::shared_ptr<shaders::shader> shd;
      if(shdopt.has_value())
      {
        shd = shdopt.value();
      }
      else{
        // TOOD: error handle
      }
      shd->use();
      std::array<float, 4> verts = {
        start.x, start.y,
        end.x,   end.y
                    };
      unsigned int elements[] = {0, 1};

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

    bool line2d::operator==(line2d const& rhs) const
    {
      return (start == rhs.start) && (end == rhs.end);
    }
  }
}

namespace std
{
  template<>
  struct hash<we::graphics::line2d>
  {
    std::size_t operator()(we::graphics::line2d const& l)
    {
      std::size_t seed = 0;
      boost::hash_combine(seed, l.start.x);
      boost::hash_combine(seed, l.start.y);
      boost::hash_combine(seed, l.end.x);
      boost::hash_combine(seed, l.end.y);
      return seed;
    }
  };
}