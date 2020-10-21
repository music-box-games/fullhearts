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

#include <unordered_map>

#include "graphic_buffer_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      static std::unordered_map<std::string, vao_handle::buffer_t> vaos;
      static std::unordered_map<std::string, vbo_handle::buffer_t> vbos;
      static std::unordered_map<std::string, ebo_handle::buffer_t> ebos;

      vao_handle::vao_handle(graphics::buffers::vertex_array_object & d) : data(d) {}
      vao_handle::~vao_handle() {}
      std::optional<vao_handle> vao_handle::new_handle(std::string const& name)
      {
        if(vaos.count(name))
        {
          // fails if a buffer with this name already exists
          return {};
        }
        else
        {
          vaos.at(name) = vao_handle::buffer_t(name);
          return vao_handle(vaos.at(name));
        }
      }

      std::optional<vao_handle> vao_handle::get_handle(std::string const& name)
      {
        if(vaos.count(name))
        {
          return vao_handle(vaos.at(name));
        }
        else
        {
          // fail if none exist
          return {};
        }
      }

      vbo_handle::vbo_handle(graphics::buffers::vertex_buffer_object & d) : data(d) {}
      vbo_handle::~vbo_handle() {}
      std::optional<vbo_handle> vbo_handle::new_handle(std::string const& name)
      {
        if(vbos.count(name))
        {

          // fails if exists already
          return {};
        }
        else
        {
          vbos.at(name) = vbo_handle::buffer_t(name);
          return vbo_handle(vbos.at(name));
        }
      }
      std::optional<vbo_handle> vbo_handle::get_handle(std::string const& name)
      {
        if(vbos.count(name))
        {
          return vbo_handle(vbos.at(name));
        }
        else
        {
          return {};
        }
      }

      ebo_handle::ebo_handle(graphics::buffers::element_buffer_object & d) : data(d) {}
      ebo_handle::~ebo_handle() {}
      std::optional<ebo_handle> ebo_handle::new_handle(std::string const& name)
      {
        if(ebos.count(name))
        {
          return {};
        }
        else
        {
          ebos.at(name) = ebo_handle::buffer_t(name);
          return ebo_handle(ebos.at(name));
        }
      }

      std::optional<ebo_handle> ebo_handle::get_handle(std::string const& name)
      {
        if(ebos.count(name))
        {
          return ebo_handle(ebos.at(name));
        }
        else
        {
          return {};
        }
      }
    }
  }
}