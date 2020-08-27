/****************************************************************************
 *   Copyright (C) 2020 by Music Box Games                                  *
 *                                                                          *
 *   This file is part of WaifuEngine                                       *
 *                                                                          *
 *   WaifuEngine is free software: you can redistribute it and/or modify it *
 *   under the terms of the MIT License.                                    *
 *                                                                          *
 *   WaifuEngine is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   MIT License for more details.                                          *
 *                                                                          *
 *   You should have received a copy of the MIT License along with          *
 *   WaifuEngine.  If not, see https://opensource.org/licenses/MIT          *
 ****************************************************************************/

/******************************************************************************/
/**
* @file   coordinates.cc
* @author Ryan Hanson
* @par    email: iovita\@musicboxgames.net
* @brief Provides logic for converting between screen and world coordinates.
*/
/******************************************************************************/

#include "coordinates.hpp"
#include "window.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    /**
      * Converts world coordinates to screen coordinates.
      * @param c World coordinates to convert. Between (0,0) and (window_width, window_height).
      * @return Corresponding screen coordinates. Between(-1,-1) and (1,1).
    */
    glm::vec2 world_coordinates_to_screen_coordinates(glm::vec2 c)
    {
      // first get ratio of each coordinate to the screen's dimensions.
      float world_ratio_x = c.x / get_current_window()->get_width();
      float world_ratio_y = c.y / get_current_window()->get_height();
      // take that ratio to get the equivalent value between 0-2 (because -1 to 1 is a difference of 2)
      // then subtract 1 to set it to our coordinates between -1 and 1.
      float screen_c_x = (world_ratio_x * 2.0f) - 1.0f;
      float screen_c_y = (world_ratio_y * 2.0f) - 1.0f;
      return glm::vec2(screen_c_x, screen_c_y);
    }

    /**
      * Converts screen coordinates to world coordinates.
      * @param c Screen coordinates to convert.
      * @return Corresponding world coordinates.
    */
    glm::vec2 screen_coordinates_to_world_coordinates(glm::vec2 c)
    {
      // add 1 to each coordinate to move it all to positive
      // divide by 2 to get ratio
      float screen_ratio_x = (c.x + 1.0f) / 2.0f;
      float screen_ratio_y = (c.y + 1.0f) / 2.0f;
      // multiply the window's width and height by the ratio to get the positions
      float world_c_x = screen_ratio_x * get_current_window()->get_width();
      float world_c_y = screen_ratio_y * get_current_window()->get_height();
      return glm::vec2(world_c_x, world_c_y);
    }
  }
}