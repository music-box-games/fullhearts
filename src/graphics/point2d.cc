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
* @file   point2d.cc
* @author Ryan Hanson
* @date   27 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  2D point abstraction.
*
*/
/******************************************************************************/

#include "point2d.hpp"
#include "coordinates.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    /**
      * @brief Converts a point in window space to screen space.
      * @param p The point in window space.
      * @return The equivalent point in screen space.
    */
    screen_point_2d window_point_2d_to_screen_point_2d(window_point_2d p)
    {
      return window_coordinates_to_screen_coordinates(p);
    }

    /**
      * @brief Converts a point in screen space to window space.
      * @param p The point in screen space.
      * @return The equivalent point in window space.
    */
    window_point_2d screen_point_2d_to_window_point_2d(screen_point_2d p)
    {
      return screen_coordinates_to_window_coordinates(p);
    }
  }
}
