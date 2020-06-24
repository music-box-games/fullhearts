#include "graphics_primatives.hpp"
#include "window.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace primatives
    {
      triangle::triangle(std::string name) : base_primative(name), shd(new shaders::shader(shaders::vertex_shader("default"), shaders::fragment_shader("default")))
      {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

      }

      triangle::~triangle()
      {
        delete shd;
        shd = nullptr;
      }

      void triangle::update(float)
      {

      }

      void triangle::draw() const
      {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        shd->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
      }

      void triangle::set_vertices(float verts[9])
      {
        for(int i = 0; i < 9; ++i)
        {
          vertices[i] = verts[i];
        }
      }
    }
  } // namespace graphics
} // namespace waifuengine