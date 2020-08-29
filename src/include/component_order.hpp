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
* @file   component_order.hpp
* @author Ryan Hanson
* @date   29 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Order of components
*
*/
/******************************************************************************/

#ifndef _WE_COMPONENT_ORDER_HPP_
#define _WE_COMPONENT_ORDER_HPP_

namespace waifuengine
{
  namespace components
  {
    namespace order
    {

    enum component_order
    {
      sprite = 0,
      physics,
      physics2,
      transform,
      collider,
      mouse_collider,
      script_object,
      dummy,
      debug_draw, // should be last so it can draw on top of everything
    };
    }
  }
}

#endif