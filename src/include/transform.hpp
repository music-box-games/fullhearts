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
* @file   transform.hpp
* @author Ryan Hanson
* @par    email: iovita\@musicboxgames.net
* @brief  Transform
*/
/******************************************************************************/

#ifndef _WE_TRANSFORM_HPP_
#define _WE_TRANSFORM_HPP_

#include <array>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "debug.hpp"
#include "component.hpp"
#include "coordinates.hpp"
#include "point2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    struct decomposed_transform
    {
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;
    };

    class rect_dimensions
    {
    public:
      glm::vec2 center;
      glm::vec2 dimensions;

      std::array<glm::vec2, 4> vertices; // top-left, top-right, bottom-right, bottom-left

      /**
      * @brief Constructor
      * @param c Center of the rectangle
      * @param d Dimensions of the rectangle
      */
      rect_dimensions(glm::vec2 c, glm::vec2 d);
    };

    // transform class
    /*

      

    */
    class transform
    {
    private:
      friend class waifuengine::core::debug::imgui_listener;
      glm::mat4 trans; // transform matrix
      bool dirty; // if true, transform matrix needs to be recalculated
      glm::vec2 scale_; // x and y scale
      world_point_2d pos_; // position in world coordinates defaults to 0,0
      float rot_deg; // degrees rotation
     
      /**
      * @brief Calculates the transform matrix, sets dirty to false
      */
      void calculate_transform();

    public:
      enum class axis
      {
        x,
        y,
        z,
      };

      /**
      * @brief Constructor
      */
      transform();
      /**
      * @brief Destructor
      */
      virtual ~transform();

      /**
      * @brief Updates the transform
      */
      virtual void update();
      /**
      * @brief Draws the transform (if needed)
      */
      virtual void draw() const;
      /**
      * @brief Resets the transform to default values
      */
      void reset();
      /**
      * @brief Rotates the transform by the given number of degrees
      * @param degrees Value to rotate by
      */
      void rotate(float degrees);
      /**
      * @brief Sets the rotation to the given value
      * @param degrees Value to set rotation to
      */
      void set_rotation(float degrees);
      /**
      * @brief Gets the rotation in degrees
      * @return Degrees of rotation
      */
      float rotate() const;
      /**
      * @brief Translates by the given distance
      * @param distance Distance to translate by in world coordinates
      */
      void translate(world_coordinates_2d distance);
      /**
      * @brief Sets the translation of the object to the given position
      * @param position Where to set translation to in World Coordinates
      */
      void set_translation(world_point_2d position);
      /**
      * @brief Gets the translation of the transform
      * @return Returns the position of the transform
      */
      glm::vec2 translate() const;
      /**
      * @brief Uniformly scales each dimension by the given value
      * @param s Value to scale by
      */
      void uniform_scale(float s);
      /**
      * @brief Scales the transform by the provided values
      * @param s Values to scale by
      */
      void scale(glm::vec2 s);
      /**
      * @brief Sets the scale to the provided values
      * @param s Values to set scale to
      */
      void set_scale(glm::vec2 s);
      /**
      * @brief Gets the scale of the transform
      * @return Scale
      */
      glm::vec2 scale() const;
      
      int width_in_pixels() const;
      int height_in_pixels() const;

      void set_width_in_pixels(int width);
      void set_height_in_pixels(int height);

      void set_dimensions_in_pixels(glm::vec2 d);
      glm::vec2 dimensions_in_pixels() const;

      [[deprecated]] glm::vec2 position_in_pixels() const;


      /**
        * @brief Gets the screen coordinates for the center of the object
        * @return Object's screen coordinates.
      */
      screen_point_2d get_position_in_screen_coordinates() const;

      /**
        * @brief Gets the world coordinates for the center of the object
        * @return Object's world coordinates.
      */
      world_point_2d get_position_in_world_coordinates() const;

      window_point_2d get_position_in_window_coordinates() const;

      /**
        * @brief Sets the center of the object to the position given in screen coordinates.
        * @param p Point in screen coordinates to set position to.
      */
      void set_position_in_screen_coordinates(screen_point_2d p);

      /**
        * @brief Sets the center of the object to the position given in world coordinates.
        * @param p Point in world coordinates to set position to.
      */
     void set_position_in_window_coordinates(window_point_2d p);

     /**
       * @brief Sets the "width" of the object.
       * 
       * The width ratio is a ratio of the width of the object to the width of the window.
       * 
       * @param wr Ratio of object width to window width.
     */
     void set_width_ratio(float wr);

      /**
        * @brief Sets the "height" of the object.
        * 
        * The height ratio is a ratio of the height of the object to the height of the window.
        * 
        * @param wh Ratio of object height to window height.
      */
      void set_height_ratio(float wh);

      /**
        * @brief Gets the width ratio of the object.
        * @return The object's width ratio.
      */
      float get_width_ratio() const;

      /**
        * @brief Gets the height ratio of the object.
        * @return The object's height ratio.
      */
      float get_height_ratio() const;

      /**
        * @brief Sets the width and height ratios
        * @param r Ratios for width and height
      */
      void set_ratios(glm::vec2 r);
      
      void lock_screen_proportion(bool set = true);
      /**
      * @brief Gets a pointer to the transform matrix
      * @return Pointer to transform matrix
      */
      glm::mat4 *data();
      /**
      * @brief Gets a const pointer to the transform matrix
      * @return Const pointer to transform matrix
      */
      glm::mat4 const * const_data() const;
      /**
      * @brief Gets a copy of the transform matrix
      * @return Copy of transform matrix
      */
      glm::mat4 matrix() const;

      /**
      * @brief Decomposes a matrix into its parts.
      * @return Decomposed transform matrix
      */
      decomposed_transform decompose() const;

      bool operator==(transform const& rhs) const;
      bool operator!=(transform const& rhs) const;
    };
  } // namespace graphics
} // namespace waifuengine

#endif