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

#include <memory>
#include <optional>

#include "graphic_buffers.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      class vao_handle
      {
      public:
        using buffer_t = graphics::buffers::vertex_array_object;

        buffer_t& data;

        vao_handle(graphics::buffers::vertex_array_object & d);
        ~vao_handle();

        static std::optional<vao_handle> new_handle(std::string const& name);
        static std::optional<vao_handle> get_handle(std::string const& name);

      };

      class vbo_handle
      {
      public:
        using buffer_t = graphics::buffers::vertex_buffer_object;

        buffer_t& data;

        vbo_handle(graphics::buffers::vertex_buffer_object & d);
        ~vbo_handle();

        static std::optional<vbo_handle> new_handle(std::string const& name);
        static std::optional<vbo_handle> get_handle(std::string const& name);
      };

      class ebo_handle
      {
      public:
        using buffer_t = graphics::buffers::element_buffer_object;

        buffer_t& data;

        ebo_handle(graphics::buffers::element_buffer_object & d);
        ~ebo_handle();

        static std::optional<ebo_handle> new_handle(std::string const& name);
        static std::optional<ebo_handle> get_handle(std::string const& name);
      };

      template<class Buffer_Type>
      std::optional<Buffer_Type> get_buffer_handle(std::string const& name)
      {
        return Buffer_Type::get_handle(name);
      }

      template<class Buffer_Type>
      std::optional<Buffer_Type> new_buffer_handle(std::string const& name)
      {
        return Buffer_Type::new_handle(name);
      } 
    }
  }
}

#endif