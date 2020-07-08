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
        if(!disabled_ && calculating_vertices)
        {
          
        }
      }

      void triangle::calculate_vertices(bool set)
      {
        calculating_vertices = set;
      }

      void triangle::draw() const
      {
        if(!disabled_)
        {
          glBindVertexArray(VAO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(float), vertices, GL_STATIC_DRAW);
          glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
          glEnableVertexAttribArray(0);
          float timeValue = glfwGetTime();
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
        if(vertices)
        {
          delete vertices;
          vertices = nullptr;
        }
        vertices = new float[vert_count];
        for(int i = 0; i < length; ++i)
        {
          vertices[i] = verts[i];
        }
      }

      void triangle::set_shader(std::string name)
      {
        auto s = shaders::get_shader(name);
        if(s.has_value())
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

      sized_rectangle::sized_rectangle(std::string name) : base_primative(name) 
      {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
      }

      void sized_rectangle::update(float)
      {
        if (!disabled_)
        {

        }
      }

      void sized_rectangle::set_width(float w)
      {
        width = w;
      }

      void sized_rectangle::set_height(float h)
      {
        height = h;
      }

      void sized_rectangle::set_center(glm::vec2 c)
      {
        center = c;
      }

      void sized_rectangle::set_color(glm::vec4 c)
      {
        color = c;
      }

      void sized_rectangle::set_shader(std::string n)
      {
        auto s = shaders::get_shader(n);
        if(s.has_value())
        {
          shd = s.value();
        }
      }

      void sized_rectangle::set_alpha(float a)
      {
        alpha = we::utils::clamp<float>(0.f, 1.f, a);
      }

      float sized_rectangle::get_alpha() const
      {
        return alpha;
      }

      void sized_rectangle::draw() const
      {

        if (!disabled_)
        {
          int screen_width = we::core::settings::read_t<int>("window_width");
          int screen_height = we::core::settings::read_t<int>("window_height");
          float half_width = (width * screen_width) / 2.0f; // half rectangle width in pixels
          float half_height = (height  * screen_height) / 2.0f; // half rectangle height in pixels

        float top_left_x =      center.x - half_width;
        float top_left_y =      center.y + half_height;
        float top_right_x =     center.x + half_width;
        float top_right_y =     center.y + + half_height;
        float bottom_right_x =  center.x + half_width;
        float bottom_right_y =  center.y - half_height;
        float bottom_left_x =   center.x - half_width;
        float bottom_left_y =   center.y - half_height;

        glm::vec2 top_left = {top_left_x, top_left_y};
        glm::vec2 top_right = {top_right_x, top_right_y};
        glm::vec2 bottom_right = {bottom_right_x, bottom_right_y};
        glm::vec2 bottom_left = {bottom_left_x, bottom_left_y};

        std::array<float, 20> vertices = {
          // position                           // color        
           top_left[0],  top_left[1],           0.0f, 0.0f, 0.0f,  
           top_right[0], top_right[1],          0.0f, 0.0f, 0.0f,  
           bottom_right[0], bottom_right[1],    0.0f, 0.0f, 0.0f,  
           bottom_left[0], bottom_left[1],      0.0f, 0.0f, 0.0f,  
        };


          unsigned int elements[] =
          {
            0,1,2,
            2,3,0
          };

          shd->use();
          shd->set_float_4("color", color.x, color.y, color.z, color.w);
          shd->set_float_1("c_alpha", alpha);

          glBindVertexArray(VAO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

          int position_attribute = glGetAttribLocation(shd->get_id(), "position");
          glEnableVertexAttribArray(position_attribute);
          glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

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
          if(!disabled_)
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
    } // namespace shaders
  } // namespace graphics
} // namespace waifuengine