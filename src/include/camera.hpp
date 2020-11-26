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
* @file   camera.hpp
* @author Ryan Hanson
* @par    email: iovita\@musicboxgames.net
* @brief  Camera
*/
/******************************************************************************/

#ifndef _WE_CAMERA_HPP_
#define _WE_CAMERA_HPP_

#include <tuple>

#include "point2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class camera
    {
    private:
      world_coordinates_2d position;
      float rotation;

    public:
      camera();
      ~camera();

      float get_rotation_degrees() const;
      void set_rotation_degrees(float r);
      float get_rotation_radians() const;
      void set_rotation_radians(float r);

      world_coordinates_2d get_position() const;
      void set_position(world_coordinates_2d pos);

      std::tuple<world_coordinates_2d, world_coordinates_2d, world_coordinates_2d, world_coordinates_2d> get_corners() const;
      std::tuple<world_coordinates_2d, world_coordinates_2d> get_projection_coordinates() const;

    };
  }
}

#endif