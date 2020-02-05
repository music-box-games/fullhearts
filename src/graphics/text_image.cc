/******************************************************************************/
/*!
\file   text_image.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Cross platform handle for text based images (rendered text)

*/
/******************************************************************************/

#include <text_image.hpp>

namespace waifuengine
{
namespace graphics
{
  text_image::text_image(std::string t, std::shared_ptr<waifuengine::graphics::font> f)
  {
    handle = std::shared_ptr<handle_type>(new handle_type(t, f));
  }

  text_image::~text_image() {}

  void text_image::draw(void * parent)
  {
    handle->draw(parent);
  }

  std::shared_ptr<text_image::handle_type> text_image::get_handle()
  {
    return handle;
  }
}
} // namespace waifuengine