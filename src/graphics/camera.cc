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
* @file   camera.cc
* @author Ryan Hanson
* @par    email: iovita\@musicboxgames.net
* @brief  Camera
*/
/******************************************************************************/

#include <glm/glm.hpp>

#include "camera.hpp"

namespace waifuengine
{
  namespace graphics
  {
    camera::camera() : position({0.0f, 0.0f}), rotation(0.0f) {}
    camera::~camera() {}

    float camera::get_rotation_degrees() const
    {
      return rotation;
    }

    void camera::set_rotation_degrees(float r)
    {
      rotation = r;
    }

    float camera::get_rotation_radians() const
    {
      return glm::radians(rotation);
    }

    void camera::set_rotation_radians(float r)
    {
      rotation = glm::degrees(r);
    }

    void camera::set_position(world_coordinates_2d c)
    {
      position = c;
    }

    world_coordinates_2d camera::get_position() const
    {
      return position;
    }
  }
}
