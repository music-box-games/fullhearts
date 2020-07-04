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
      std::string name_;

    public:
      image(fs::path p);
      ~image();
      unsigned char * data();
      glm::vec2 dimensions() const;
      std::string name() const;
    };

    using imageptr = std::shared_ptr<image>;
  }
}

#endif