#ifndef _WE_BASIC_SHAPE_HPP_
#define _WE_BASIC_SHAPE_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <component.hpp>

namespace waifuengine
{
  namespace components
  {
    // draws basic shapes on the screen
    class basic_shape : public component<basic_shape>
    {
    public:
      COMPONENT_NAME(basic_shape);

      basic_shape();
      virtual ~basic_shape();

      virtual void update(float dt) = 0;
      virtual void draw() const = 0;
    };

    class basic_triangle : public basic_shape
    {
    private:
      unsigned int vao, vbo;

      static constexpr float triangle_data[] = 
      {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
      };


    public:
      COMPONENT_NAME(basic_triangle);

      basic_triangle();
      virtual ~basic_triangle();

      virtual void update(float dt) override;
      virtual void draw() const override;
    };
  }
}

#endif // !_WE_BASIC_SHAPE_HPP_