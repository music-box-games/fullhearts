#ifndef _WE_GRAPHICS_VALUES_HPP_
#define _WE_GRAPHICS_VALUES_HPP_

#include <glm/vec2.hpp>

namespace waifuengine
{
  namespace graphics
  {
    constexpr unsigned int RES_UHD_WIDTH = 3840;
    constexpr unsigned int RES_UHD_HEIGHT = 2160;
    constexpr unsigned int RES_QHD_WIDTH = 2560;
    constexpr unsigned int RES_QHD_HEIGHT = 1440;
    constexpr unsigned int RES_FHD_WIDTH = 1920;
    constexpr unsigned int RES_FHD_HEIGHT = 1080;

    namespace resolutions
    {
      constexpr glm::vec2 UHD = {RES_UHD_WIDTH, RES_UHD_HEIGHT};
      constexpr glm::vec2 QHD = {RES_QHD_WIDTH, RES_QHD_HEIGHT};
      constexpr glm::vec2 FHD = {RES_FHD_WIDTH, RES_FHD_HEIGHT};
    }
  }
}

#endif