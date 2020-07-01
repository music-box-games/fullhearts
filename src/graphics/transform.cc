#include "transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    transform::transform()
    {
      trans = glm::mat4(1.0f);
      scale_ = {1.0f, 1.0f};
      pos_ = {0.0f, 0.0f};
      rot_deg = 0.0f;
      dirty = true;
    }

    transform::~transform()
    {

    }

    void transform::update(float dt)
    {
      // recalc if dirty each frame to allow tweaks in imgui, store raaw vals and then make mat
      if(dirty)
      {
        trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(scale_, 1.0f));
        trans = glm::rotate(trans, glm::radians(rot_deg), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(pos_, 0.0f));
        dirty = false;
      }
    }

    void transform::draw() const
    {

    }

    void transform::rotate(float degrees)
    {
      rot_deg = degrees;
      if(rot_deg < -360.0f)
      {
        rot_deg += 360.0f;
      }
      if(rot_deg > 360.0f)
      {
        rot_deg -= 360.0f;
      }
      dirty = true;
    }

    void transform::translate(glm::vec2 distance)
    {
      pos_ = distance;
      dirty = true;
    }

    void transform::scale(glm::vec2 s)
    {
      scale_ = s;
      dirty = true;
    }

    void transform::uniform_scale(float s)
    {
      scale_ = { s, s };
      dirty = true;
    }

    glm::mat4 * transform::data()
    {
      return &trans;
    }
  }
}