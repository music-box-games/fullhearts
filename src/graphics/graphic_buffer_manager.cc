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
* @file   buffer_manager.cc
* @author Ryan hanson
* @date   11 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Manages OpenGL buffers to allow for triviable copying of objects
*         with buffers as members.
*
* 
*/
/******************************************************************************/

#include "graphic_buffer_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      vao_handle::vao_handle(graphics::buffers::vertex_array_object &const d) : data(d) {}
      vao_handle::~vao_handle() {}

      vbo_handle::vbo_handle(graphics::buffers::vertex_buffer_object &const d) : data(d) {}
      vbo_handle::~vbo_handle() {}

      ebo_handle::ebo_handle(graphics::buffers::element_buffer_object &const d) : data(d) {}
      ebo_handle::~ebo_handle() {}
    }
  }
}