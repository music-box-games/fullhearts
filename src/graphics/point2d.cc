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
      * @brief Converts a point in world space to screen space.
      * @param p The point in world space.
      * @return The equivalent point in screen space.
    */
    screen_point2d world_point2d_to_screen_point2d(world_point2d p)
    {
      return world_coordinates_to_screen_coordinates(p);
    }

    /**
      * @brief Converts a point in screen space to world spacej.
      * @param p The point in screen space.
      * @return The equivalent point in world space.
    */
    world_point2d screen_point2d_to_world_point2d(screen_point2d p)
    {
      return screen_coordinates_to_world_coordinates(p);
    }
  }
}
