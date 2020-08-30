#include "sprite.hpp"
#include "window.hpp"

#include <sstream>
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    sprite::sprite(std::string const& tex_name) : components::component<sprite>()
    {
      {
        std::stringstream ss;
        ss << "Constructing sprite with texture: " << tex_name;
        log::LOGTRACE(ss.str());
      }
      tex = textures::get_texture(tex_name).value();
    }
    sprite::~sprite() 
    {
      log::LOGTRACE("Destructing sprite");
    }

    void sprite::update(float dt)
    {
      trans.update(dt);
      if(locked_to_parent_transform)
      {
        if(!parent->has_component<transform>())
        {
          return;
        }
        auto transform_ptr = parent->get_component<transform>();
        if (!transform_ptr.use_count())
        {
          // something we wrong
          return;
        }
        tex->update(*transform_ptr);
      }
      else
      {
        tex->update(trans);
      }
    }
    
    void sprite::draw() const
    {
      if(!disabled)
      {
        tex->draw();
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

    void sprite::lock_transform_to_parent_transform(bool set) 
    {
      locked_to_parent_transform = set;
    }

    bool sprite::transform_locked_to_parent() const
    {
      return locked_to_parent_transform;
    }
  }
}

BOOST_CLASS_EXPORT_IMPLEMENT(we::graphics::sprite);