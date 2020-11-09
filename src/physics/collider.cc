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
* @file   collider.cc
* @author Ryan Hanson
* @date   27 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Basic rectangle collider logic.
*/
/******************************************************************************/

#include "collider.hpp"
#include "sprite.hpp"
#include "colors.hpp"
#include "log.hpp"
#include "window.hpp"
#include "draw_rects.hpp"
#include "shader.hpp"
#include "polygon.hpp"
#include "colors.hpp"
#include "coordinates.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace physics
  {
    collider::collider() : components::component<collider>(), colliding(false), width(0), height(0)
    {
      log::LOGTRACE("Constructing collider");
    }

    collider::~collider()
    {
      log::LOGTRACE("Destructing collider");
    }

    void collider::update(float dt)
    {
      if (!disabled)
      {
        // TODO: update position of debug draw if debugging
        if (debugging && !allow_manual_collider_editing)
        {
          // ensure that the parent object even has a transform
          if (!parent->has_component<graphics::transform>())
          {
            return;
          }
          // build polygon
          // find positions of each corner of the collider to create line segments
          // get the parent transform
          std::shared_ptr<graphics::transform> parent_trans = parent->get_component<graphics::transform>();
          // set width and height from parent transform
          set_width(parent_trans->get_width_ratio());
          set_height(parent_trans->get_height_ratio());

          // get point for the parent transform, which is center of the object
          graphics::screen_point_2d parent_position = parent_trans->get_position_in_screen_coordinates();

          float rect_width = width;   // screen coordinate width (so a ratio of rect width to window width from 0-1)
          float rect_height = height; // height " "

          // calculate the corners of the rectangle
          graphics::screen_point_2d bottom_left(parent_position.x - rect_width, parent_position.y - rect_height);
          graphics::screen_point_2d top_left(bottom_left.x, parent_position.y + rect_height);
          graphics::screen_point_2d top_right(parent_position.x + rect_width, top_left.y);
          graphics::screen_point_2d bottom_right(top_right.x, bottom_left.y);

          // counter clockwise starting at bottom left point
          debug_square = graphics::rect2d({bottom_left, bottom_right}, {bottom_right, top_right}, {top_right, top_left}, {top_left, bottom_left});
        }
      }
    }

    void collider::draw() const
    {
    }

    bool collider::is_colliding() const
    {
      return colliding;
    }

    void collider::set_width(float wr)
    {
      width = wr;
    }

    void collider::set_height(float hr)
    {
      height = hr;
    }

    void collider::draw_debug()
    {
      if ((!disabled) && debugging)
      {
        if (is_colliding())
        {
          debug_square.draw(graphics::colors::get_color(graphics::colors::color_name::red), 1.0f);
        }
        else
        {
          debug_square.draw(graphics::colors::get_color(graphics::colors::color_name::green), 1.0f);
        }
      }
    }

    void collider::offset_translate(glm::vec2 translation)
    {
      offset.translate(translation);
    }

    void collider::offset_set_translation(glm::vec2 translation)
    {
      offset.set_translation(translation);
    }

    glm::vec2 collider::offset_get_translation()
    {
      return offset.translate();
    }

    void collider::offset_rotate(float degrees)
    {
      offset.rotate(degrees);
    }

    void collider::offset_set_rotation(float degrees)
    {
      offset.set_rotation(degrees);
    }

    float collider::offset_get_rotation()
    {
      return offset.rotate();
    }

    void collider::offset_scale(glm::vec2 s)
    {
      offset.scale(s);
    }

    void collider::offset_set_scale(glm::vec2 s)
    {
      offset.set_scale(s);
    }

    glm::vec2 collider::offset_get_scale()
    {
      return offset.scale();
    }

    void collider::offset_scalex(float s)
    {
      offset_scale(glm::vec2(s, offset_get_scaley()));
    }

    void collider::offset_scaley(float sy)
    {
      offset_scale(glm::vec2(offset_get_scalex(), sy));
    }

    float collider::offset_get_scalex()
    {
      return offset.scale().x;
    }

    float collider::offset_get_scaley()
    {
      return offset.scale().y;
    }

    namespace collisions
    {
      bool point_rectangle(glm::vec2 point, graphics::rect_dimensions rect)
      {
        if (point.x < rect.vertices[0].x)
        {
          return false;
        }
        else if (point.x > rect.vertices[1].x)
        {
          return false;
        }
        else if (point.y > rect.vertices[1].y)
        {
          return false;
        }
        else if (point.y < rect.vertices[2].y)
        {
          return false;
        }
        return true;
      }
    } // namespace collisions
  }   // namespace physics
} // namespace waifuengine