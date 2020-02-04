#include <sdl_text.hpp>

namespace waifuengine
{
namespace graphics
{
namespace sdl
{

font::font(std::string path, int pt)
{
  fd = TTF_OpenFont(path.c_str(), pt);
  // TODO: impl validation
}

font::~font()
{
  TTF_CloseFont(fd);
}

font::data_type * font::data()
{
  return fd;
}

}
} // namespace graphics
} // namespace waifuengine