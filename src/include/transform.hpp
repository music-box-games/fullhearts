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
#include <SFML/Graphics.hpp>

#include "debug.hpp"
#include "component.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class transform
    {
    public:
      transform();
      transform(transform const& rhs);
      ~transform();

      void translate(float x, float y);
      void translate(glm::vec2 p);
      void translate(sf::Transformable const& t);
      void translate(transform const& t);
      void set_translation(float x, float y);
      void set_translation(glm::vec2 p);
      void set_translation(sf::Transformable const& t);
      void set_translation(transform const& t);
      glm::vec2 translation() const;

      void rotate(float r);
      void rotate(sf::Transformable const& t);
      void rotate(transform const& t);
      void set_rotation(float r);
      void set_rotation(sf::Transformable const& t);
      void set_rotation(transform const& t);
      float rotation() const;

      void scale(float x, float y);
      void scale(glm::vec2 s);
      void scale(sf::Transformable const& t);
      void scale(transform const& t);
      void set_scale(float x, float y);
      void set_scale(glm::vec2 s);
      void set_scale(sf::Transformable const& t);
      void set_scale(transform const& t);
      glm::vec2 scale() const;

      sf::Transformable data() const;

      bool operator==(sf::Transformable const& rhs);
      bool operator==(transform const& rhs);
      bool operator!=(sf::Transformable const& rhs);
      bool operator!=(transform const& rhs);
      
      transform& operator=(transform const& rhs);
      transform& operator=(transform const&& rhs);

      static sf::Vector2f glm_vec2_to_sfml_vec2(glm::vec2 v);
      static glm::vec2 sfml_vec2_to_glm_vec2(sf::Vector2f v);
      static glm::vec2 sfml_vec2_to_glm_vec2(sf::Vector2i v);
    private:
      sf::Transformable tr;

    };
  } // namespace graphics
} // namespace waifuengine

#endif