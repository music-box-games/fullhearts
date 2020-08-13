#include "sprite.hpp"
#include "window.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite(std::string const& tex_name) : components::component<sprite>()
    {
      tex = textures::get_texture(tex_name).value();
    }
    sprite::~sprite() {}

    void sprite::update(float dt)
    {
      trans.update(dt);
      tex->update(dt);
    }
    void sprite::draw() const
    {
      if(!disabled)
      {
      tex->draw(trans);
      }
    }

    void sprite::set_texture(std::string const& name)
    {
      tex = textures::get_texture(name).value();
    }

    void sprite::rotate(float degrees)
    {
      trans.rotate(degrees);
    }

    void sprite::set_rotation(float d)
    {
      trans.set_rotation(d);
    }

    float sprite::rotate() const
    {
      return trans.rotate();
    }

    void sprite::translate(glm::vec2 d)
    {
      trans.translate(d);
    }

    void sprite::set_translation(glm::vec2 p)
    {
      trans.set_translation(p);
    }

    glm::vec2 sprite::translate() const
    {
      return trans.translate();
    }

    void sprite::scale(glm::vec2 s)
    {
      trans.scale(s);
    }

    void sprite::set_scale(glm::vec2 s)
    {
      trans.set_scale(s);
    }

    glm::vec2 sprite::scale() const
    {
      return trans.scale();
    }

    void sprite::scale_to_window()
    {
      // TODO maybe need to calc this differently
      auto w = get_current_window();
      auto d = tex->texture_dimensions();
      glm::vec2 w_d{w->get_width(), w->get_height()};
      glm::vec2 s{w_d.x / d.x, w_d.y / d.y};
      scale(s);
    }
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::graphics::sprite);