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
* @file   buffer_manager.hpp
* @author Ryan hanson
* @date   18 Sept 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Manages OpenGL buffers to allow for triviable copying of objects
*         with buffers as members.
*
* 
*/
/******************************************************************************/

#ifndef _WE_GRAPHIC_BUFFER_MANAGER_HPP_
#define _WE_GRAPHIC_BUFFER_MANAGER_HPP_

#include "graphic_buffers.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      class vao_handle
      {
      private:
        graphics::buffers::vertex_array_object &const data;

      public:
        vao_handle(graphics::buffers::vertex_array_object & d);
        ~vao_handle();
      };

      class vbo_handle
      {
      private:
        graphics::buffers::vertex_buffer_object &const data;

      public:
        vbo_handle(graphics::buffers::vertex_buffer_object & d);
        ~vbo_handle();
      };

      class ebo_handle
      {
      private:
        graphics::buffers::element_buffer_object &const data;

      public:
        ebo_handle(graphics::buffers::element_buffer_object & d);
        ~ebo_handle();
      };
    }
  }
}

#endif