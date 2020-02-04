#include <font.hpp>

namespace waifuengine
{
namespace graphics
{
  using fptr = std::shared_ptr<font::font_handle>;

  font::font(std::string path, int pt)
  {
    handle = fptr(new font_handle(path, pt));
  }

  font::~font() {}

  fptr font::data()
  {
    return handle;
  }
}
}
