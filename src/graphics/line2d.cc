
#include <boost/container_hash/hash.hpp>

#include <array>

#include "line2d.hpp"
#include "shader.hpp"
#include "graphics.hpp"
#include "log.hpp"
#include "graphic_buffer_manager.hpp"

constexpr std::size_t RAND_STR_LEN = 256;

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    // TODO: hook this up with the buffer manager to allow trivial copying of class
    line2d::line2d(point_2d s, point_2d e) : start(s), end(e), 
    VAO(buffer_manager::new_buffer_handle<buffer_manager::vao_handle>(utils::random_str(RAND_STR_LEN)).value()),
    VBO(buffer_manager::new_buffer_handle<buffer_manager::vbo_handle>(utils::random_str(RAND_STR_LEN)).value())
    {
      
    }

    line2d::line2d() : start(glm::vec2(0.f, 0.f)), end(glm::vec2(0.f, 0.f)),
    VAO(buffer_manager::new_buffer_handle<buffer_manager::vao_handle>(utils::random_str(RAND_STR_LEN)).value()),
    VBO(buffer_manager::new_buffer_handle<buffer_manager::vbo_handle>(utils::random_str(RAND_STR_LEN)).value())
    {
    }

    line2d::~line2d() 
    {
    }

    void line2d::draw(glm::vec3 color, float alpha)
    {
      auto shdopt = shaders::get_shader("line_shader");
      std::shared_ptr<shaders::shader> shd;
      if(shdopt.has_value())
      {
        shd = shdopt.value();
      }
      else
      {
        // TODO: error handle
        std::stringstream ss;
        ss << "Shader has invalid value!";
        log::LOGERROR(ss.str());
        return;
      }
      shd->use();
      std::array<float, 4> verts = 
      {
        start.x, start.y,
        end.x,   end.y
      };

      shd->set_float_3("color", color.r, color.g, color.b);
      shd->set_float_1("alpha", alpha);

      glBindVertexArray(VAO.data.data());
      glBindBuffer(GL_ARRAY_BUFFER, VBO.data.data());
      glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

      int position_attribute = shd->get_attribute("position");
      glEnableVertexAttribArray(position_attribute);
      glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_LINES, 0, 2);
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