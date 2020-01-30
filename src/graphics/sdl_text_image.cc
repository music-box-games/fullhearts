#include <sdl_text_image.hpp>

#ifdef WE_GRAPHICS_SDL2

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
namespace sdl2
{
  text_image_handle::text_image_handle() : t_("") {}
  text_image_handle::text_image_handle(std::string t) : t_(t) {}
  text_image_handle::text_image_handle(text_image_handle const& other) : t_(other.t_) {}
  text_image_handle::~text_image_handle() {}

  void text_image_handle::text(std::string t)
  {
    t_ = t;
  }

  std::string text_image_handle::text() const
  {
    return t_;
  }

  void text_image_handle::draw() const
  {
    // TODO: actually render text
  }
}
} // namespace graphics
} // namespace waifuengine

#endif