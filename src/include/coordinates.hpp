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

namespace waifuengine
{
  namespace graphics
  {
    /**
      * Converts world coordinates to screen coordinates.
      * @param c World coordinates to convert. Between (0,0) and (window_width, window_height).
      * @return Corresponding screen coordinates. Between (-1,-1) and (1,1).
    */
    glm::vec2 world_coordinates_to_screen_coordinates(glm::vec2 c);
    /**
      * Converts screen coordinates to world coordinates.
      * @param c Screen coordinates to convert. Between (-1,-1) and (1,1).
      * @return Corresponding world coordinates. Between (0,0) and (window_width, window_height).
    */
    glm::vec2 screen_coordinates_to_world_coordinates(glm::vec2 c);

    using screen_coordinates = glm::vec2;
    using world_coordinates = glm::vec2;

    constexpr int SCREEN_COORD_RANGE = 2;
  }
}

#endif