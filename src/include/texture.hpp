/******************************************************************************/
/*!
\file   texture.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Texture class, handles texturing and drawing textures.

*/
/******************************************************************************/

#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include <memory>
#include <optional>

#include <component.hpp>

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {

    class texture : public components::component<texture>
    {
    private:
      unsigned int texture_id;
      bool valid;
      void load_texture(std::string file);

    public:
      COMPONENT_NAME(texture);
      COMPONENT_TYPE(texture);

      texture(std::string file);
      texture(texture const& other);
      ~texture();

      void update(float dt);
      void draw() const;

      bool is_valid() const;
    };

    std::optional<std::shared_ptr<texture>> load_texture(std::string file, std::string name);
    std::optional<std::shared_ptr<texture>> get_texture(std::string name);

      void init();
      void shutdown();
    }
  }
}

#endif // !_WE_TEXTURE_HPP_