#include <s_image.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <SDL_image.h>

#include <utils.hpp>
#include <graphics.hpp>
#include <window.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  image_handle::image_handle() : data(nullptr) {}
  image_handle::~image_handle()
  {
    SDL_DestroyTexture(data);
    data = nullptr;
  }

  void image_handle::load_image(std::string file)
  {
    SDL_Surface * load = IMG_Load(file.c_str());
    if(load == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error!", "Could not load image");
      std::exit(-1);
    }
    
    data = SDL_CreateTextureFromSurface(we::graphics::get_window()->data()->get_renderer(), load);
    if(data == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error!", "Could not create texture!");
      std::exit(-1);
    }
    SDL_FreeSurface(load);
  }

  image_handle::image_type * image_handle::get_image()
  {
    return data;
  }

  bool image_handle::valid() const
  {
    return !(data == nullptr);
  }

  void image_handle::draw() const
  {
    //if(!data) return;
    SDL_RenderCopy(we::graphics::get_window()->data()->get_renderer(), data, NULL, NULL);
  }

  void image_handle::release_image()
  {
    SDL_DestroyTexture(data);
    data = nullptr;
  }
}
} // namespace graphics
} // namespace waifuengine

#endif // WE_GRAPHICS_SDL2