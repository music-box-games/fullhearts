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
* @file   coordinates.hpp
* @author Ryan Hanson
* @par    email: iovita\@musicboxgames.net
* @brief Provides logic for converting between screen and world coordinates.
*/
/******************************************************************************/

#ifndef _WE_COORDINATES_HPP_
#define _WE_COORDINATES_HPP_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "window.hpp"


namespace waifuengine
{
  namespace graphics
  {
    using coordinate_type_2d = glm::vec2;
    using screen_coordinates_2d = coordinate_type_2d;
    using window_coordinates_2d = coordinate_type_2d;

    using coordinate_type_3d = glm::vec3;

    /**
      * Converts world coordinates to screen coordinates.
      * @param c World coordinates to convert. Between (0,0) and (window_width, window_height).
      * @return Corresponding screen coordinates. Between (-1,-1) and (1,1).
    */
    screen_coordinates_2d window_coordinates_to_screen_coordinates(window_coordinates_2d c, float window_width = get_current_window()->get_width(), float window_height = get_current_window()->get_height());
    /**
      * Converts screen coordinates to world coordinates.
      * @param c Screen coordinates to convert. Between (-1,-1) and (1,1).
      * @return Corresponding world coordinates. Between (0,0) and (window_width, window_height).
    */
    window_coordinates_2d screen_coordinates_to_window_coordinates(screen_coordinates_2d c, float window_width = get_current_window()->get_width(), float window_height = get_current_window()->get_height());


    bool lax_coordinate_compare(coordinate_type_2d const& a, coordinate_type_2d const& b, float error);

    constexpr int SCREEN_COORD_RANGE = 2;
  }
}

#endif