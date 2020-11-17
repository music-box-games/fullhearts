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
* @file   point2d.hpp
* @author Ryan Hanson
* @date   27 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  2D point abstraction.
*
*/
/******************************************************************************/

#ifndef _WE_POINT2D_HPP_
#define _WE_POINT2D_HPP_

#include <glm/vec2.hpp>
#include "coordinates.hpp"

namespace waifuengine
{
  namespace graphics
  {
    using point_2d = glm::vec2;
    using screen_point_2d = screen_coordinates_2d;
    using window_point_2d = window_coordinates_2d;
    using world_point_2d = world_coordinates_2d;

    /**
      * @brief Converts a point in window space to screen space.
      * @param p The point in window space.
      * @return The equivalent point in screen space.
    */
    screen_point_2d window_point_2d_to_screen_point_2d(window_point_2d p);

    /**
      * @brief Converts a point in screen space to world spacej.
      * @param p The point in screen space.
      * @return The equivalent point in window space.
    */
    window_point_2d screen_point_2d_to_window_point_2d(screen_point_2d p);
  }
}


#endif