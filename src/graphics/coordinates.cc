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
#include "num_utils.hpp"

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
    screen_coordinates_2d window_coordinates_to_screen_coordinates(window_coordinates_2d c, float window_width, float window_height)
    {
      // first get ratio of each coordinate to the screen's dimensions.
      float world_ratio_x = c.x / window_width;
      float world_ratio_y = c.y / window_height;
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
    window_coordinates_2d screen_coordinates_to_window_coordinates(screen_coordinates_2d c, float window_width, float window_height)
    {
      // add 1 to each coordinate to move it all to positive
      // divide by 2 to get ratio
      float screen_ratio_x = (c.x + 1.0f) / 2.0f;
      float screen_ratio_y = (c.y + 1.0f) / 2.0f;
      // multiply the window's width and height by the ratio to get the positions
      float world_c_x = screen_ratio_x * window_width;
      float world_c_y = screen_ratio_y * window_height; 
      return glm::vec2(world_c_x, world_c_y);
    }

    bool lax_coordinate_compare(coordinate_type_2d const& a, coordinate_type_2d const& b, float error)
    {
      return utils::lax_float_compare(a.x, b.x, error) && utils::lax_float_compare(a.y, b.y, error);     
    }
  }
}