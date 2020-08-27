#include "transform.hpp"
#include "settings.hpp"
#include "window.hpp"

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
          return (static_cast<float>(core::settings::read_t<int>("window_width")) / ((p != 0.0f) ? p : p + 0.001f)) - 1.0f;
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
      // recalc if dirty each frame to allow tweaks in imgui
      if(dirty)
      {
        trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(scale_, 1.0f));
        trans = glm::rotate(trans, glm::radians(rot_deg), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(pos_, 0.0f));
        dirty = false;
      }
    }

    int transform::width_in_pixels() const
    {
      return scale().x * static_cast<int>(graphics::get_current_window()->get_width());
    }

    int transform::height_in_pixels() const
    {
      return scale().y * static_cast<int>(graphics::get_current_window()->get_height());
    }

    glm::vec2 transform::dimensions_in_pixels() const
    {
      return glm::vec2(width_in_pixels(), height_in_pixels());
    }

    glm::vec2 transform::position_in_pixels() const
    {
      return get_position_in_world_coordinates();
    }

    screen_point2d transform::get_position_in_screen_coordinates() const
    {
      return pos_;
    }

    world_point2d transform::get_position_in_world_coordinates() const
    {
      return screen_point2d_to_world_point2d(get_position_in_screen_coordinates());
    }

    void transform::set_position_in_screen_coordinates(screen_point2d p)
    {
      pos_ = p;
      dirty = true;
    }

    void transform::set_position_in_world_coordinates(world_point2d p)
    {
      set_position_in_screen_coordinates(world_point2d_to_screen_point2d(p));
      dirty = true;
    }

    void transform::set_width_ratio(float wr)
    {
      width_ratio = wr;
    }

    void transform::set_height_ratio(float wh)
    {
      height_ratio = wh;
    }

    float transform::get_width_ratio() const
    {
      return width_ratio;
    }

    float transform::get_height_ratio() const
    {
      return height_ratio;
    }

    void transform::draw() const
    {

    }

    void transform::rotate(float degrees)
    {
      rot_deg += degrees;
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

    void transform::set_rotation(float d)
    {
      rot_deg = d;
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
      pos_ += distance;
      dirty = true;
    }

    void transform::set_translation(glm::vec2 t)
    {
      pos_ = t;
      dirty = true;
    }

    glm::vec2 transform::translate() const
    {
      auto dt = decompose();
      return glm::vec2{dt.translation.x, dt.translation.y};
    }

    void transform::scale(glm::vec2 s)
    {
      scale_ += s;
      dirty = true;
    }

    glm::vec2 transform::scale() const
    {
      auto dt = decompose();
      return glm::vec2{dt.scale.x, dt.scale.y};
    }

    void transform::set_scale(glm::vec2 s)
    {
      scale_ = s;
      dirty = true;
    }

    void transform::uniform_scale(float s)
    {
      scale_ += glm::vec2(s,s);
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