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
      tex->draw(trans);
    }

    void sprite::set_texture(std::string const& name)
    {
      tex = textures::get_texture(name).value();
    }

    void sprite::rotate(float degrees)
    {
      trans.rotate(degrees);
    }

    void sprite::translate(glm::vec2 d)
    {
      trans.translate(d);
    }

    void sprite::scale(glm::vec2 s)
    {
      trans.scale(s);
    }

    void sprite::scale_to_window()
    {
      auto w = get_current_window();
      auto d = tex->texture_dimensions();
      glm::vec2 w_d{w->get_width(), w->get_height()};
      glm::vec2 s{w_d.x / d.x, w_d.y / d.y};
      scale(s);
    }
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::graphics::sprite);