#include <SOIL2/SOIL2.h>

#include "image.hpp"

namespace waifuengine
{
  namespace graphics
  {
    image::image(fs::path p)
    {
      data_ = SOIL_load_image(p.string().c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    }

    image::~image()
    {
      SOIL_free_image_data(data_);
    }

    unsigned char * image::data()
    {
      return data_;
    }

    glm::vec2 image::dimensions() const
    {
      return {width, height};
    }
  }
}