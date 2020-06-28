#ifndef _WE_IMAGE_HPP_
#define _WE_IMAGE_HPP_

#include <memory>
#include <glm/glm.hpp>

#include "filesystem.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class image
    {
    private:
      unsigned char * data_;
      int height;
      int width;

    public:
      image(fs::path p);
      ~image();
      unsigned char * data();
      glm::vec2 dimensions() const;
    };

    using imageptr = std::shared_ptr<image>;
  }
}

#endif