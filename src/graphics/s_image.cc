#include <s_image.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <utils.hpp>
#include <graphics.hpp>

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
    SDL_FreeSurface(data);
    data = nullptr;
  }

  void image_handle::load_image(std::string file)
  {
    data = SDL_LoadBMP(file.c_str());
    if(data == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error!", "Could not load SDL_Surface from BMP");
      std::exit(-1);
    }
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
    SDL_BlitSurface(data, NULL, SDL_GetWindowSurface(we::graphics::get_window()->data()->data()), NULL);
  }

  void image_handle::release_image()
  {
    SDL_FreeSurface(data);
    data = nullptr;
  }
}
} // namespace graphics
} // namespace waifuengine

#endif // WE_GRAPHICS_SDL2