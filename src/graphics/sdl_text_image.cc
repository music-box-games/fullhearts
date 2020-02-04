/******************************************************************************/
/*!
\file   sdl_text_image.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  SDL handle for text images

*/
/******************************************************************************/

#include <sdl_text_image.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <SDL_ttf.h>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  text_image_handle::text_image_handle(std::string t) : t_(t), data(nullptr)
  {
    
  }

  text_image_handle::~text_image_handle()
  {
    SDL_DestroyTexture(data);
  }

  void text_image_handle::draw(void * p) const
  {
    // TODO: actually render text
  }
}
} // namespace graphics
} // namespace waifuengine

#endif