#include "transform.hpp"
#include "settings.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    rect_dimensions::rect_dimensions(glm::vec2 c, glm::vec2 d) : center(c), dimensions(d)
    {
      vertices[0] = { center.x - (dimensions.x / 2), center.y + (dimensions.y / 2) };
      vertices[1] = { center.x + (dimensions.x / 2), center.y + (dimensions.y / 2) };
      vertices[2] = { center.x + (dimensions.x / 2), center.y - (dimensions.y / 2) };
      vertices[3] = { center.x - (dimensions.x / 2), center.y - (dimensions.y / 2) };
    }

    float transform::convert_pixels_to_screen_coords(float p, transform::axis a)
    {
      switch(a)
      {
        case axis::x:
          return (static_cast<float>(core::settings::read_t<int>("window_width")) / ((p!= 0.0f) ? p : p + 0.001f)) - 1.0f;
        case axis::y:
          return (static_cast<float>(core::settings::read_t<int>("window_height")) / ((p != 0.0f) ? p : p + 0.001f)) - 1.0f;
        default:
          return 0.0f;
      }
    }

    transform::transform() : components::component<transform>()
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

    float transform::rotate() const
    {
      auto dt = decompose();
      return glm::angle<float>(dt.rotation);
    }

    void transform::translate(glm::vec2 distance)
    {
      pos_ = distance;
      dirty = true;
    }

    glm::vec2 transform::translate() const
    {
      auto dt = decompose();
      return glm::vec2{dt.translation.x, dt.translation.y};
    }

    void transform::scale(glm::vec2 s)
    {
      scale_ = s;
      dirty = true;
    }

    glm::vec2 transform::scale() const
    {
      auto dt = decompose();
      return glm::vec2{dt.scale.x, dt.scale.y};
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

    decomposed_transform transform::decompose() const
    {
      decomposed_transform dt;
      glm::decompose(trans, dt.scale, dt.rotation, dt.translation, dt.skew, dt.perspective);
      dt.rotation = glm::conjugate(dt.rotation);
      return dt;
    }
  }
}