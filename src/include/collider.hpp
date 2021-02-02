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
* @file   collider.hpp
* @author Ryan Hanson
* @date   27 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Basic rectangle collider logic.
*
*/
/******************************************************************************/

#ifndef _WE_COLLIDER_HPP_
#define _WE_COLLIDER_HPP_

#include "debug.hpp"
#include "component.hpp"
#include "gameobject.hpp"
#include "transform.hpp"

// TODO: collision layers, only check in layer

namespace waifuengine
{
  namespace physics
  {
    class collider : public waifuengine::components::component<collider>
    {
    public:
      COMPONENT_REGISTER(collider);
    };

    namespace collisions
    {
    }
  }
}

#endif