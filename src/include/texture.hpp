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

#include <component.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class texture : public components::component<texture>
    {
    private:
      unsigned int texture_id;
      
    public:
      COMPONENT_NAME(texture);
      COMPONENT_TYPE(texture);

      texture();
      texture(std::string file);
      texture(texture const& other);
      ~texture();

      void load_texture(std::string file);

    };
  }
}

#endif // !_WE_TEXTURE_HPP_