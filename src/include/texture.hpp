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
    public:
      COMPONENT_NAME(texture);
      COMPONENT_TYPE(texture);

      texture();
      texture(texture const& other);
      ~texture();

    };
  }
}

#endif // !_WE_TEXTURE_HPP_