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
#include <gameobject.hpp>

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

  void image_handle::draw(void * p) const
  {
    waifuengine::object_management::gameobject* parent = reinterpret_cast<waifuengine::object_management::gameobject*>(p);
    we::physics::transform * t = dynamic_cast<we::physics::transform *>(parent->get_component<we::physics::transform>().get());
    if(!t)
    {
      SDL_RenderCopy(we::graphics::get_window()->data()->get_renderer(), data, NULL, NULL);
    }
    else
    {
      SDL_Rect r = t->get();
      // SDL uses top left corner as (0,0), including for the dsrect for SDL_RenderCopy.
      // So we need to convert the x,y coords stored in transform to that they represent the top left of the object
      SDL_Rect adjusted_coords;
      adjusted_coords.x = r.x - (r.w / 2);
      adjusted_coords.y = r.y - (r.h / 2);
      adjusted_coords.w = r.w;
      adjusted_coords.h = r.h;
      SDL_RenderCopy(we::graphics::get_window()->data()->get_renderer(), data, NULL, &adjusted_coords);
    }
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