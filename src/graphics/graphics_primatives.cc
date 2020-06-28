#include "graphics_primatives.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "num_utils.hpp"

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

      void sized_rectangle::set_shader(std::string n)
      {
        auto s = shaders::get_shader(n);
        if(s.has_value())
        {
          shd = s.value();
        }
      }

      void sized_rectangle::draw() const
      {
        if (!disabled_)
        {
          static float vertices[20] = { 0.0f };
          int screen_width = we::core::settings::read_t<int>("window_width");
          int screen_height = we::core::settings::read_t<int>("window_height");
          float half_width = (width * screen_width) / 2.0f; // half rectangle width in pixels
          float half_height = (height  * screen_height) / 2.0f; // half rectangle height in pixels

          float left_x = (screen_width * (center[0] + 0.5f)) - half_width; // left x value in pixels
          float right_x = (screen_width * (center[0] + 0.5f)) + half_width; // right x value in pixels
          float top_y = (screen_height * (center[1] + 0.5f)) + half_height; // top y value in pixels
          float bottom_y = (screen_height * (center[1] + 0.5f)) - half_height; // bottom y value in pixels

          // convert values to screen coords
          left_x = utils::clamp<float>(-1.0f, 1.0f, left_x / float(screen_width));
          right_x = utils::clamp<float>(-1.0f, 1.0f, right_x / float(screen_width));
          top_y = utils::clamp<float>(-1.0f, 1.0f, top_y / float(screen_height));
          bottom_y = utils::clamp<float>(-1.0f, 1.0f, bottom_y / float(screen_height));

          vertices[0] = left_x;   // top left x
          vertices[1] = top_y; // top left y
          vertices[2] = 1.0f; // top left r
          vertices[3] = 0.0f; // top left g
          vertices[4] = 0.0f; // top left b

          vertices[5] = right_x;   // top right x
          vertices[6] = top_y; // top right y
          vertices[7] = 0.0f; // top right r
          vertices[8] = 1.0f; // top right g
          vertices[9] = 0.0f; // top right b

          vertices[10] = right_x;   // bottom right x
          vertices[11] = bottom_y; // bottom right y
          vertices[12] = 0.0f; // bottom right r
          vertices[13] = 0.0f; // bottom right g
          vertices[14] = 1.0f; // bottom right b

          vertices[15] = left_x;  // bottom left x
          vertices[16] = bottom_y; // bottom left y
          vertices[17] = 1.0f; // bottom left r
          vertices[18] = 1.0f; // bottom left g
          vertices[19] = 1.0f; // bottom left b

          float vert[20] =
          {
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f
          };

          unsigned int elements[] =
          {
            0,1,2,
            2,3,0
          };

          glBindVertexArray(VAO);
          glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

          int position_attribute = glGetAttribLocation(shd->get_id(), "position");
          glEnableVertexAttribArray(position_attribute);
          glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

          int color_attribute = glGetAttribLocation(shd->get_id(), "color");
          glEnableVertexAttribArray(color_attribute);
          glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

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