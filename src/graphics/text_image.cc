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
  text_image::text_image() {}
  text_image::text_image(std::string t)
  {
    handle.text(t);
  }
  text_image::text_image(text_image const& other)
  {
    handle.text(other.text());
  }

  text_image::~text_image() {}

  void text_image::text(std::string t)
  {
    handle.text(t);
  }

  std::string text_image::text() const
  {
    return handle.text();
  }

  void text_image::draw() const
  {
    handle.draw();
  }
}
} // namespace waifuengine