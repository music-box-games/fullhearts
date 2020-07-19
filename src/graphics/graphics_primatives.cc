#include "graphics_primatives.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "num_utils.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace primatives
    {
      triangle::triangle(std::string name) : base_primative(name), vertices(nullptr)
      {
        shd = shaders::get_shader("default").value();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
      }

      triangle::~triangle()
      {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
      }

      void triangle::update(float)
      {
        if (!disabled_ && calculating_vertices)
        {
        }
      }

      void triangle::calculate_vertices(bool set)
      {
        calculating_vertices = set;
      }

      void triangle::draw() const
      {
        if (!disabled_)
        {
          glBindVertexArray(VAO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(float), vertices, GL_STATIC_DRAW);
          glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
          glEnableVertexAttribArray(0);
          float timeValue = static_cast<float>(glfwGetTime());
          float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
          shd->use();
          shd->set_float_4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
          glBindVertexArray(VAO);
          glDrawArrays(GL_TRIANGLES, 0, 3);
        }
      }

      void triangle::set_vertices(float *verts, int length)
      {
        vert_count = length;
        if (vertices)
        {
          delete vertices;
          vertices = nullptr;
        }
        vertices = new float[vert_count];
        for (int i = 0; i < length; ++i)
        {
          vertices[i] = verts[i];
        }
      }

      void triangle::set_shader(std::string name)
      {
        auto s = shaders::get_shader(name);
        if (s.has_value())
        {
          shd = s.value();
        }
      }

      void triangle::set_width(float w)
      {
        width = w;
      }

      void triangle::set_height(float h)
      {
        height = h;
      }

      void triangle::set_center(glm::vec2 c)
      {
        center = c;
      }

      float triangle::get_width() const
      {
        return width;
      }

      float triangle::get_height() const
      {
        return height;
      }

      glm::vec2 triangle::get_center() const
      {
        return center;
      }

      rectangle::rectangle(std::string name) : base_primative(name)
      {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
      }

      void rectangle::update(float dt)
      {
        if (!disabled_)
        {
          std::scoped_lock lock(lock_);



          static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
          std::for_each(components_.begin(), components_.end(), f);
        }
      }

      void rectangle::set_width(float w)
      {
        width = w;
      }

      void rectangle::set_height(float h)
      {
        height = h;
      }

      void rectangle::set_center(glm::vec2 c)
      {
        center = c;
      }

      void rectangle::set_color(glm::vec4 c)
      {
        color = c;
      }

      void rectangle::set_shader(std::string n)
      {
        auto s = shaders::get_shader(n);
        if (s.has_value())
        {
          shd = s.value();
        }
      }

      void rectangle::set_alpha(float a)
      {
        alpha = we::utils::clamp<float>(0.f, 1.f, a);
      }

      float rectangle::get_alpha() const
      {
        return alpha;
      }

      void rectangle::draw() const
      {
        if (!disabled_)
        {
          std::array<float, 8> vertices = {
            -1.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f
          };

          unsigned int elements[] =
              {
                  0, 1, 2,
                  2, 3, 0
              };

          shd->use();
          shd->set_float_4("color", color.r, color.g, color.b, color.a);

          // write vertex data
          glBindVertexArray(VAO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

          // set element data
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

          int position_attribute = shd->get_attribute("position");
          glEnableVertexAttribArray(position_attribute);
          glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);


          // TODO: get transform component from parent object and use that for transforms
          graphics::transform * const trf = dynamic_cast<graphics::transform *>(get_component_const<graphics::transform>().get());
          int transform_attribute = shd->get_attribute("transform");
          glUniformMatrix4fv(transform_attribute, 1, GL_FALSE, nullptr); // set transform in shader

          glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
        }
      }

    } // namespace primatives

    namespace shaders
    {
      namespace test
      {
        test_triangle0::test_triangle0(std::string name) : primatives::triangle(name) {}

        test_triangle1::test_triangle1(std::string name) : primatives::triangle(name) {}

        void test_triangle1::draw() const
        {
          if (!disabled_)
          {
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(float), vertices, GL_STATIC_DRAW);
            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            shd->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
          }
        }
      } // namespace test
    }   // namespace shaders
  }     // namespace graphics
} // namespace waifuengine