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

    void transform::update(float) {}

    void transform::draw() const {}

    void transform::rotate(float rotation)
    {
      glm::rotate(matrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void transform::translate(glm::vec3 vec)
    {
      glm::translate(matrix, vec);
    }

    void transform::scale(glm::vec3 vec)
    {
      glm::scale(matrix, vec);
    }

    float transform::rotation()
    {
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;

      glm::decompose(matrix, scale, rotation, translation, skew, perspective);

      return 0.0f;
    }

    glm::vec3 transform::translation()
    {
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;

      glm::decompose(matrix, scale, rotation, translation, skew, perspective);

      return translation;  
    }

    glm::vec3 transform::scale()
    {
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;

      glm::decompose(matrix, scale, rotation, translation, skew, perspective);

      return scale;
    }

  }
}