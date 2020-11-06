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
#include "shader.hpp"
#include "graphics_primatives.hpp"
#include "transform.hpp"
#include "rect2d.hpp"
#include "line2d.hpp"

// TODO: collision layers, only check in layer

namespace waifuengine
{
  namespace physics
  {
    class collider : public waifuengine::components::component<collider>
    {
    protected:
      friend class core::debug::imgui_listener;
      graphics::rect2d debug_square;
      graphics::transform offset; /**< transform offset from the parent object's transform */
      bool colliding; /**< if this collider is currently involved in a collision */
      float width; /**< Width ratio of collider */
      float height; /**< Height ratio of collider */
      bool allow_manual_collider_editing = false; /**< allows manually editing the collider in debug mode */

    public:
      COMPONENT_REGISTER(collider);

      collider();
      virtual ~collider();

      virtual void update(float dt);
      virtual void draw() const;
      virtual void draw_debug();


      /**
       * @brief Sets the collider's width to be a ratio of the window's width.
       * @param ratio The width ratio to set.
      */
      void set_width(float ratio);

      /**
        * @brief Sets the collider's height to be a ratio of the window's height.
        * @param ratio The height ratio to set.
      */
      void set_height(float ratio);

      void offset_translate(glm::vec2 translation);
      void offset_set_translation(glm::vec2 translation);
      glm::vec2 offset_get_translation();

      void offset_rotate(float rotation);
      void offset_set_rotation(float rotation);
      float offset_get_rotation();

      void offset_scale(glm::vec2 scale);
      void offset_set_scale(glm::vec2 scale);
      glm::vec2 offset_get_scale();
      void offset_scalex(float scale);
      void offset_scaley(float scale);
      float offset_get_scalex();
      float offset_get_scaley();

      bool is_colliding() const;
    };

    namespace collisions
    {
      bool point_rectangle(glm::vec2 point, graphics::rect_dimensions rect);
    }
  }
}

#endif