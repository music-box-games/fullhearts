#ifndef _WE_SPRITE_HPP_
#define _WE_SPRITE_HPP_

#include <component.hpp>
#include <serialization.hpp>
#include "texture.hpp"
#include "transform.hpp"
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class sprite : public components::component<sprite>
    {
    private:
      friend class waifuengine::core::debug::imgui_listener;
      textures::textureptr tex;
      transform trans;

      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const)
      {
        ar & boost::serialization::base_object<components::component<sprite>>(*this);
      }

    public:
      COMPONENT_NAME(sprite);
      COMPONENT_TYPE(sprite);
      
      sprite(std::string const& tex_name = "default");
      virtual ~sprite();

      virtual void update(float dt) override;
      virtual void draw() const override;

      void set_texture(std::string const& name);

      void rotate(float degrees);
      void translate(glm::vec2 dist);
      void scale(glm::vec2 s);

      float rotate() const;
      glm::vec2 translate() const;
      glm::vec2 scale() const;

      void scale_to_window();

      
    };
    typedef std::shared_ptr<sprite> spriteptr;
  }
}
BOOST_CLASS_EXPORT_KEY(we::components::component<we::graphics::sprite>);
BOOST_CLASS_EXPORT_KEY(waifuengine::graphics::sprite);

#endif