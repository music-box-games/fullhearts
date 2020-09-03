#include "transform.hpp"
#include "settings.hpp"
#include "window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "log.hpp"

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


    transform::transform() : components::component<transform>()
    {
      log::LOGTRACE("Constructing transform");
      trans = glm::mat4(1.0f);
      scale_ = {1.0f, 1.0f};
      pos_ = {0.0f, 0.0f};
      rot_deg = 0.0f;
      width_ratio = 0.0f;
      height_ratio = 0.0f;
      dirty = true;
    }

    transform::~transform()
    {
      log::LOGTRACE("Destructing transform");
    }

    void transform::calculate_transform()
    {
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(pos_, 0.0f));
      trans = glm::rotate(trans, glm::radians(rot_deg), glm::vec3(0.0, 0.0f, 1.0f));
      trans = glm::scale(trans, glm::vec3(scale_, 1.0f));
      dirty = false;
    }

    void transform::update(float dt)
    {
      // recalc if dirty each frame to allow tweaks in imgui
      if(dirty)
      {
        calculate_transform();
      }
    }

    int transform::width_in_pixels() const
    {
      return static_cast<int>(scale().x * static_cast<int>(graphics::get_current_window()->get_width())); // cast to int because we can't have a fraction of a pixel anyways
    }

    int transform::height_in_pixels() const
    {
      return static_cast<int>(scale().y * static_cast<int>(graphics::get_current_window()->get_height()));
    }

    glm::vec2 transform::dimensions_in_pixels() const
    {
      return glm::vec2(width_in_pixels(), height_in_pixels());
    }

    glm::vec2 transform::position_in_pixels() const
    {
      return get_position_in_window_coordinates();
    }

    screen_point_2d transform::get_position_in_screen_coordinates() const
    {
      return pos_;
    }

    window_point_2d transform::get_position_in_window_coordinates() const
    {
      return screen_point_2d_to_window_point_2d(get_position_in_screen_coordinates());
    }

    void transform::set_position_in_screen_coordinates(screen_point_2d p)
    {
      pos_ = p;
      dirty = true;
    }

    void transform::set_position_in_window_coordinates(window_point_2d p)
    {
      int b = 0;
      int a = 1 / b;
      set_position_in_screen_coordinates(window_point_2d_to_screen_point_2d(p));
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

    void transform::set_ratios(glm::vec2 r)
    {
      set_width_ratio(r.x);
      set_height_ratio(r.y);
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

    glm::mat4 const * transform::const_data() const
    {
      return & trans;
    }

    glm::mat4 transform::matrix() const
    {
      return trans;
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