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
#include <color.hpp>
#include <graphics.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  text_image_handle::text_image_handle(std::string t, std::shared_ptr<waifuengine::graphics::font> f) : t_(t), f_(f), data(nullptr)
  {
    // create surface
    SDL_Surface * surface = TTF_RenderText_Solid(f_->data()->data(), t_.c_str(), we::graphics::convert_color(we::graphics::colors::black));
    // allocate texture
    data = SDL_CreateTextureFromSurface(we::graphics::get_window()->data()->get_renderer(), surface);
    // maybe something about dimensions
    SDL_FreeSurface(surface);
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