#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include "filesystem.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class texture
    {
    private:
      unsigned int txtr;
    public:
      texture(fs::path file);
      ~texture();

      void draw() const;

      void load(fs::path file);
    };

    using textureptr = std::shared_ptr<texture>;
  }
}

#endif