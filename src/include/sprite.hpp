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
      textures::texture tex; /**< pointer to the texture this sprite uses */
      transform trans; /**< the sprite's transform, separate from the parent object */
      bool locked_to_parent_transform; /**< if the sprite should just use the transform from the parent object instead of its own */

      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const)
      {
        ar & boost::serialization::base_object<components::component<sprite>>(*this);
      }

    public:
      COMPONENT_REGISTER(sprite);
      
      sprite(std::string const& tex_name = "default");
      virtual ~sprite();

      virtual void update(float dt) override;
      virtual void draw() const override;

      void set_texture(std::string const& name);

      void rotate(float degrees);
      void set_rotation(float degrees);
      void translate(glm::vec2 dist);
      void set_translation(glm::vec2 p);
      void scale(glm::vec2 s);
      void set_scale(glm::vec2 s);

      float rotate() const;
      glm::vec2 translate() const;
      glm::vec2 scale() const;

      void scale_to_window();

      /**
        * @brief Makes the sprite use the parent's transform instead.
        * @param set To set or not to set.
      */
      void lock_transform_to_parent_transform(bool set = true);

      /**
        * @brief Checks if the sprite is using its parent's transform instead of its own.
        * @return If using the parent's transform.
      */
      bool transform_locked_to_parent() const;

      
    };
    typedef std::shared_ptr<sprite> spriteptr;
  }
}
BOOST_CLASS_EXPORT_KEY(we::components::component<we::graphics::sprite>);
BOOST_CLASS_EXPORT_KEY(waifuengine::graphics::sprite);

#endif