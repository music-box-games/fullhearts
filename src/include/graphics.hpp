#ifndef _WE_GRAPHICS_HPP_
#define _WE_GRAPHICS_HPP_

#include <string>

namespace waifuengine
{
  namespace graphics
  {
    void init(std::string title);
    void shutdown();

    void present();
    void clear();
  }
}

#endif