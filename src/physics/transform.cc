/******************************************************************************/
/*!
\file   transform.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  transform component for applying transforms to objects.

*/
/******************************************************************************/

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <transform.hpp>

namespace waifuengine
{
  namespace physics
  {
    transform::transform() : matrix(glm::mat4(1.0f)) {}
    transform::transform(transform const& other) : matrix(other.matrix) {}
    transform::~transform() {}

    void update(float) {}

    void draw() const {}

    void rotate(float rotation)
    {
      glm::rotate(matrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void translate(glm::vec3 vec)
    {
      glm::translate(matrix, vec);
    }

    void scale(glm::vec3 vec)
    {
      glm::scale(matrix, vec);
    }

  }
}