#include <s_image.hpp>

#ifdef WE_GRAPHICS_SDL2

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
    SDL_FreeSurface(data);
    data = nullptr;
  }

  void image_handle::load_image(std::string file)
  {
    SDL_Surface * load = SDL_LoadBMP(file.c_str());
    if(load == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error!", "Could not load SDL_Surface from BMP");
      std::exit(-1);
    }
    
    data = SDL_ConvertSurface(load, SDL_GetWindowSurface(we::graphics::get_window()->data()->data())->format, 0);
    if(data == NULL)
    {
      utils::notify(utils::notification_type::mb_ok, "Fatal Error!", "Could not convert SDL_Surface!");
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