#include "transform.hpp"

namespace waifuengine
{
  namespace graphics
  {
    transform::transform() : tr(sf::Transformable()) {}
    transform::transform(transform const& rhs) : tr(rhs.tr) {}
    transform::~transform() {}

    void transform::translate(float x, float y)
    {
      tr.move(x,y);
    }

    void transform::translate(glm::vec2 t)
    {
      translate(t.x, t.y);
    }

    void transform::translate(transform const& t)
    {
      translate(t.tr);
    }

    void transform::translate(sf::Transformable const& t)
    {
      tr.move(t.getPosition());
    }

    void transform::set_translation(float x, float y)
    {
      tr.setPosition(x, y);
    }

    void transform::set_translation(glm::vec2 t)
    {
      tr.setPosition(t.x, t.y);
    }

    void transform::set_translation(sf::Transformable const& t)
    {
      set_translation(sfml_vec2_to_glm_vec2(t.getPosition()));
    }

    void transform::set_translation(transform const& t)
    {
      set_translation(t.translation());
    }

    glm::vec2 transform::translation() const
    {
      return transform::sfml_vec2_to_glm_vec2(tr.getPosition());
    }

    void transform::rotate(float r)
    {
      tr.rotate(r);
    }

    void transform::rotate(transform const& t)
    {
      rotate(t.rotation());
    }

    void transform::rotate(sf::Transformable const& t)
    {
      rotate(t.getRotation());
    }

    void transform::set_rotation(float r)
    {
      tr.setRotation(r);
    }

    void transform::set_rotation(sf::Transformable const& t)
    {
      tr.setRotation(t.getRotation());
    }

    void transform::set_rotation(transform const& t)
    {
      set_rotation(t.rotation());
    }

    float transform::rotation() const
    {
      return tr.getRotation();
    }

    void transform::scale(float x, float y)
    {
      tr.scale(x,y);
    }

    void transform::scale(glm::vec2 s)
    {
      tr.scale(glm_vec2_to_sfml_vec2(s));
    }

    void transform::scale(transform const& t)
    {
      scale(t.scale());
    }

    void transform::scale(sf::Transformable const& t)
    {
      scale(sfml_vec2_to_glm_vec2(t.getScale()));
    }

    void transform::set_scale(float x, float y)
    {
      tr.setScale(x,y);
    }

    void transform::set_scale(glm::vec2 s)
    {
      tr.setScale(s.x, s.y);
    }

    void transform::set_scale(sf::Transformable const& t)
    {
      tr.setScale(t.getScale());
    }

    void transform::set_scale(transform const& t)
    {
      tr.setScale(glm_vec2_to_sfml_vec2(scale()));
    }

    glm::vec2 transform::scale() const
    {
      return sfml_vec2_to_glm_vec2(tr.getScale());
    }

    sf::Transformable transform::data() const
    {
      return tr;
    }

    bool transform::operator==(sf::Transformable const& rhs)
    {
      return tr.getTransform() == rhs.getTransform();
    }

    bool transform::operator==(transform const& rhs)
    {
      return (*this) == rhs.tr;
    }

    bool transform::operator!=(sf::Transformable const& rhs)
    {
      return !(tr.getTransform() == rhs.getTransform());
    }

    bool transform::operator!=(transform const& rhs)
    {
      return !((*this) == rhs.tr);
    }

    transform& transform::operator=(transform const& rhs)
    {
      tr = rhs.tr;
      return *this;
    }

    transform& transform::operator=(transform const&& rhs)
    {
      tr = rhs.tr;
      return *this;
    }

    sf::Vector2f transform::glm_vec2_to_sfml_vec2(glm::vec2 v)
    {
      return sf::Vector2f(v.x, v.y);
    }

    glm::vec2 transform::sfml_vec2_to_glm_vec2(sf::Vector2f v)
    {
      return glm::vec2(v.x, v.y);
    }

    glm::vec2 transform::sfml_vec2_to_glm_vec2(sf::Vector2i v)
    {
      return glm::vec2(v.x, v.y);
    }
  }
}