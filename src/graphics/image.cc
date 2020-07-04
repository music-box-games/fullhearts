#include <SOIL2/SOIL2.h>

#include "image.hpp"
#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    image::image(fs::path p)
    {
      name_ = p.string();
      log::LOGTRACE(std::string("Constructing image: \"" + name_ + "\""));
      data_ = SOIL_load_image(p.string().c_str(), &width, &height, 0, SOIL_LOAD_RGB);
      if(data_ == nullptr)
      {
        we::log::LOGERROR(std::string("Failed to load image: \"" + name_ + "\""));
      }
    }

    image::~image()
    {
      log::LOGTRACE(std::string("Destructing image: \"" + name_ + "\""));
      SOIL_free_image_data(data_);
    }

    std::string image::name() const
    {
      return name_;
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