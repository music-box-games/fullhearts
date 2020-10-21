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
* @file   graphic_buffers.cc
* @author Ryan Hanson
* @date   10 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Reference counted wrappers around openGL buffers
*
* 
*/
/******************************************************************************/

#include "graphic_buffers.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace buffers
    {
      vertex_array_object::vertex_array_object(std::string const& n) : name_(n)
      {
        glGenVertexArrays(1, &vao);
        // TODO: error check
      }

      vertex_array_object::~vertex_array_object()
      {
        glDeleteVertexArrays(1, &vao);
      }

      std::string vertex_array_object::name() const
      {
        return name_;
      }

      GLuint vertex_array_object::data() const
      {
        return vao;
      }

      vertex_buffer_object::vertex_buffer_object(std::string const& n) : name_(n)
      {
        glGenBuffers(1, &vbo);
      }

      vertex_buffer_object::~vertex_buffer_object()
      {
        glDeleteBuffers(1, &vbo);
      }

      std::string vertex_buffer_object::name() const
      {
        return name_;
      }

      GLuint vertex_buffer_object::data() const
      {
        return vbo;
      }

      element_buffer_object::element_buffer_object(std::string const& n) : name_(n)
      {
        glGenBuffers(1, &ebo);
      }

      element_buffer_object::~element_buffer_object()
      {
        glDeleteBuffers(1, &ebo);
      }

      std::string element_buffer_object::name() const
      {
        return name_;
      }

      GLuint element_buffer_object::data() const
      {
        return ebo;
      }
    }
  }
}