#include <s_image.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <SDL_image.h>

#include <utils.hpp>
#include <graphics.hpp>
#include <window.hpp>
#include <image.hpp>
#include <sprite.hpp>
#include <transform.hpp>
#include <glm/vec3.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  image_handle::image_handle() : data(nullptr), parent(nullptr) {}
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
    auto obj = reinterpret_cast<we::graphics::sprite *>(parent->get_parent())->parent.lock();
    auto tr = obj->get_component<we::physics::transform>();
    if(tr.use_count() == 0)
    {
      SDL_RenderCopy(we::graphics::get_window()->data()->get_renderer(), data, NULL, NULL);
    }
    else
    {
      SDL_Rect r = tr->translation();
      SDL_RenderCopy(we::graphics::get_window()->data()->get_renderer(), data, NULL, &r);
    }
  }

  void image_handle::release_image()
  {
    SDL_DestroyTexture(data);
    data = nullptr;
  }

  void image_handle::set_parent(image * p)
  {
    parent = p;
  }

  image * image_handle::get_parent()
  {
    return parent;
  }
}
} // namespace graphics
} // namespace waifuengine

#endif // WE_GRAPHICS_SDL2