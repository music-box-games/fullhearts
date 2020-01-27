#include <image.hpp>

namespace waifuengine
{
namespace graphics
{
  image::image() : handle(new handle_type()) {}
  image::~image() {}

  void image::load_file(std::string file)
  {
    handle->load_image(file);
  }

  void image::release_image()
  {
    handle->release_image();
  }

  std::shared_ptr<image::handle_type> image::get_handle()
  {
    return handle;
  }

  bool image::valid() const
  {
    return handle->valid();
  }

  void image::draw() const
  {
    handle->draw();
  }

}
} // namespace waifuengine